#include <stdio.h>
#include "header.hpp"

templateFunctionNoNamespace_struct<double, float> templateFunctionNoNamespace_struct_inst;

///////////////
// these templates mock should be generated in a separate file!
// to include here verbatim and to used in the test.
//TODO toutes les fonctions sont a générer ici
//le fichier peut etre inclus plusieurs fois?



//TODO est-il utile de vouloir faire appel dans ce cas au callback original?
//je ne pense pas. On va reellement remplacer tout le comportement?
template <typename X, typename Y>
X templateFunctionNoNamespace(X &x, Y y)
{
  int opmock_i;
  X default_res = templateFunctionNoNamespace_struct_inst.calls[0].return_value;

  //TODO gerer champ callback
  //if (templateFunctionNoNamespace_struct_inst.callback != NULL)
  //  {
        templateFunctionNoNamespace_struct_inst.actualCalls++;
        //return do_sound_struct_inst.callback (sound, do_sound_struct_inst.actualCalls);
	//  }

  if (templateFunctionNoNamespace_struct_inst.expectedCalls == 0)
    {
      printf ("WARNING : unexpected call of templateFunctionNoNamespace, returning random value.\n");
      return default_res;
    }

  templateFunctionNoNamespace_struct_inst.actualCalls++;
  
  if (templateFunctionNoNamespace_struct_inst.calls[0].check_params == 1)
    {
      //attention x est une reference il faut donc comparer par
      //defaut les pointeurs
      //je suis obligé de les caster en void a cause de bizarreries
      // dans C++ (upcast implicite en double?)
      // il me faudrait vraiment des matchers pour rendre
      //le test utile (matcher float-float par ex;
      //lui passer 2 pointeurs sur void.
      if ((void *) templateFunctionNoNamespace_struct_inst.calls[0].x != (void *)&x)
        {
	  printf("WARNING : wrong value for parameter 'x' when calling templateFunctionNoNamespace (call %d)\n", templateFunctionNoNamespace_struct_inst.actualCalls);
        }

      if (templateFunctionNoNamespace_struct_inst.calls[0].y != y)
        {
	  printf("WARNING : wrong value for parameter 'y' when calling templateFunctionNoNamespace (call %d)\n", templateFunctionNoNamespace_struct_inst.actualCalls);
        }
    }

  for(opmock_i = 1; opmock_i < templateFunctionNoNamespace_struct_inst.expectedCalls; opmock_i++)
    {
      templateFunctionNoNamespace_struct_inst.calls[opmock_i - 1] = templateFunctionNoNamespace_struct_inst.calls[opmock_i];
    }
  
  templateFunctionNoNamespace_struct_inst.expectedCalls--;
  return default_res;
}

///////////////

int main(int argc, char *argv[])
{
  templateFunctionNoNamespace_struct_inst.expectedCalls = 0;

  float param1 = 2.0;
  double res = templateFunctionNoNamespace<float, double> (param1, 3.0);
  std::cout << " result : " << res << std::endl;

std::cout << " val param1 : " << param1 << std::endl;

  return 0;
}
