#include <filesystem>
#include <iostream>
#include <string>
#include <vector>

#include <boost/program_options.hpp>
#include <inja.hpp>
#include <json.hpp>

/**
 * Parse an SVG file into JSON
 */
nlohmann::json
parseSVGfile(
  std::string const & filePath )
{
  nlohmann::json returnValue;

  return returnValue;
}

std::vector< std::filesystem::path >
findTemplateFiles(
  std::filesystem::path const & templateDirectory )
{
  std::vector< std::filesystem::path > templates;

  // Find all the template files
  if( std::filesystem::exists( templateDirectory ) &&
      std::filesystem::is_directory( templateDirectory ) )
  {

    for( auto const & entry : std::filesystem::recursive_directory_iterator( templateDirectory ) )
    {
      if( std::filesystem::is_regular_file(entry) &&
          entry.path().extension() == ".template" )
      {
          templates.emplace_back( entry.path() );
      }
    }
  }

  return templates;
}

void
generateCode(
  nlohmann::json const & svgAsJSON,
  std::filesystem::path const & templateFile,
  std::filesystem::path const & outputDirectory )
{
  inja::Environment env;

  std::filesystem::path outputFile( outputDirectory / templateFile.filename() );
  outputFile.replace_extension( "" );

  std::cout << templateFile << std::endl;


  env.write( templateFile.string(), svgAsJSON, outputFile.string() );
}


/**
 * Entry point for the application.
 */
int
main( int argc, char** argv )
{
  boost::program_options::options_description optionsDescription( "Allowed options" );

  optionsDescription.add_options()
    ( "help,h", "Print help message to stdout and exit" )
    ( "outDir,o", boost::program_options::value< std::string >(), "Directory to which generated code should be written." )
    ( "templateDir,t", boost::program_options::value< std::string >(), "Directory containing the code generation templates." )
    ( "inputFile", boost::program_options::value< std::string >(), "SVG file to process." )
  ;

  boost::program_options::positional_options_description positional;
  positional.add( "inputFile", -1 );

  boost::program_options::variables_map optionsMap;

  boost::program_options::store(
    boost::program_options::command_line_parser( argc, argv )
      .options( optionsDescription )
      .positional( positional )
      .run(),
    optionsMap );

  boost::program_options::notify( optionsMap );

  if( optionsMap.count( "help" ) )
  {
    std::cout << optionsDescription << std::endl;
    return 0;
  }

  if( ! optionsMap.count( "inputFile" ) )
  {
    std::cerr << "ERROR: No input file specified." << std::endl;
    return 1;
  }

  if( ! optionsMap.count( "templateDir" ) )
  {
    std::cerr << "ERROR: No template directory specified." << std::endl;
    return 1;
  }

  std::vector< std::filesystem::path > templateFiles(
    findTemplateFiles( optionsMap[ "templateDir" ].as< std::string >() ) );

  if( ! templateFiles.size() )
  {
    std::cerr << "WARNING: No template files found in the template directory. "
                 "No source code will be generated."
              << std::endl;
  }

  std::filesystem::path outputDirectory;

  if( optionsMap.count( "outDir" ) )
  {
    outputDirectory = optionsMap[ "outDir" ].as< std::string >();

    if( ! std::filesystem::exists( outputDirectory ) ||
        ! std::filesystem::is_directory( outputDirectory ) )
    {
      std::cerr << "ERROR: The output directory specified is invalid."
                << std::endl;

      return 1;
    }
  }
  else
  {
    std::cerr << "WARNING: No output directory specified. "
                 "Generating code into the working directory."
              << std::endl;
    outputDirectory = ".";
  }

  nlohmann::json svgAsJSON(
    parseSVGfile( optionsMap[ "inputFile" ].as< std::string >() ) );

  for( auto & templateFile : templateFiles )
  {
    generateCode(
      svgAsJSON,
      templateFile,
      outputDirectory );
  }

  return 0;
}
