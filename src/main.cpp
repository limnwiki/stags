#include "new.hpp"
#include "file.hpp"
#include "html.hpp"
#include "build.hpp"
#include "config.hpp"
#include "components.hpp"

int main(int argc, char** argv)
{
   for (int i = 0; i < argc; i++)
   {
      std::string arg = argv[i];

      if (arg == "h" || arg == "help")
      {
         std::cout << 
         "stags - STAtically Generated Site\n\n"
         "usage:\n"
         "  stags [command]\n\n"
         "commands:\n"
         "  help  (h)               prints this message\n"
         "  build (b) [default]     builds site for production \n"
         "  test  (t)               builds site with test url for testing\n"
         "  new   (n) <DIRECTORY>   creates a new stags site\n"
         ;
      }
      else if (arg == "b" || arg == "build")
      {
         load_config(CONFIG_FILE);
         variables["site_url"] = get_config("url");
         load_components();
         build_site();
      }
      else if (arg == "t" || arg == "test")
      {
         load_config(CONFIG_FILE);
         variables["site_url"] = get_config("testing_url");
         load_components();
         build_site();
      }
      else if (arg == "n" || arg == "new")
      {
         std::string dir;

         if (i+1 != argc)
            dir = argv[i+1];
         else
            dir = ".";

         create_site(dir);
      }
   }

   if (argc == 1)
   {
      load_config(CONFIG_FILE);
      variables["site_url"] = get_config("url");
      load_components();
      build_site();
   }
}