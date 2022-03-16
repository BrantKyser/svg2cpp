#include <iostream>
#include <string>

#include <boost/program_options.hpp>

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

  return 0;
}
