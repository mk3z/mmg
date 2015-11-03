/* =============================================================================
**  This file is part of the mmg software package for the tetrahedral
**  mesh modification.
**  Copyright (c) Inria - IMB (Université de Bordeaux) - LJLL (UPMC), 2004- .
**
**  mmg is free software: you can redistribute it and/or modify it
**  under the terms of the GNU Lesser General Public License as published
**  by the Free Software Foundation, either version 3 of the License, or
**  (at your option) any later version.
**
**  mmg is distributed in the hope that it will be useful, but WITHOUT
**  ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
**  FITNESS FOR A PARTICULAR PURPOSE. See the GNU Lesser General Public
**  License for more details.
**
**  You should have received a copy of the GNU Lesser General Public
**  License and of the GNU General Public License along with mmg (in
**  files COPYING.LESSER and COPYING). If not, see
**  <http://www.gnu.org/licenses/>. Please read their terms carefully and
**  use this copy of the mmg distribution only if you accept them.
** =============================================================================
*/

/**
 * \file mmgs/shared_func.h
 * \brief Common functions between MMGS library and executable.
 * \author Charles Dapogny (LJLL, UPMC)
 * \author Cécile Dobrzynski (Inria / IMB, Université de Bordeaux)
 * \author Pascal Frey (LJLL, UPMC)
 * \author Algiane Froehly (Inria / IMB, Université de Bordeaux)
 * \version 5
 * \copyright GNU Lesser General Public License.
 * \todo Doxygen documentation
 */

/* global variables */
unsigned char _MMG5_iprv2[3] = {2,0,1};
unsigned char _MMG5_inxt2[3] = {1,2,0};

/**
 * \param *prog pointer toward the program name.
 *
 * Print help for mmgs5 options.
 *
 */
static void _MMG5_usage(char *prog) {
  _MMG5_mmgUsage(prog);
  fprintf(stdout,"-A           enable anisotropy (without metric file).\n");

  fprintf(stdout,"-nreg        normal regul.\n");
#ifdef USE_SCOTCH
  fprintf(stdout,"-rn [n]      Turn on or off the renumbering using SCOTCH [0/1] \n");
#endif
  fprintf(stdout,"\n\n");

  exit(EXIT_FAILURE);
}

/**
 * \param mesh pointer toward the mesh structure.
 * \return 0 if fail, 1 if success.
 *
 * Print the default parameters values.
 *
 */
void _MMG5_defaultValues(MMG5_pMesh mesh) {

  _MMG5_mmgDefaultValues(mesh);
#ifdef USE_SCOTCH
  fprintf(stdout,"SCOTCH renumbering                  : enabled\n");
#else
  fprintf(stdout,"SCOTCH renumbering                  : disabled\n");
#endif
  fprintf(stdout,"\n\n");

  exit(EXIT_FAILURE);
}

/**
 * \param mesh pointer toward the mesh structure.
 * \param *info pointer toward the info structure.
 * \return 1.
 *
 * Store the info structure in the mesh structure.
 *
 */
static inline
int _MMG5_stockOptions(MMG5_pMesh mesh, MMG5_Info *info) {

  memcpy(&mesh->info,info,sizeof(MMG5_Info));
  _MMG5_memOption(mesh);
  if( mesh->info.mem > 0) {
    if ( mesh->npmax < mesh->np || mesh->ntmax < mesh->nt ) {
      return(0);
    } else if(mesh->info.mem < 39)
      return(0);
  }
  return(1);
}


/**
 * \param mesh pointer toward the mesh structure.
 * \param met pointer toward the sol structure.
 *
 * Set function pointers.
 *
 */
void _MMG5_setfunc(MMG5_pMesh mesh,MMG5_pSol met) {
  if ( met->size < 6 ) {
    _MMG5_calelt  = _MMG5_caltri_iso;
    _MMG5_defsiz  = _MMG5_defsiz_iso;
    gradsiz = gradsiz_iso;
    _MMG5_lenSurfEdg  = _MMG5_lenSurfEdg_iso;
    intmet  = intmet_iso;
    movintpt= movintpt_iso;
    movridpt= movridpt_iso;
  }
  else {
    fprintf(stdout,"\n  ## WARNING: ANISOTROPIC REMESHING NOT STABLE FOR NOW.\n\n");
    _MMG5_calelt  = _MMG5_caltri_ani;
    _MMG5_defsiz  = _MMG5_defsiz_ani;
    gradsiz = gradsiz_ani;
    _MMG5_lenSurfEdg  = _MMG5_lenSurfEdg_ani;
    intmet  = intmet_ani;
    movintpt= movintpt_ani;
    movridpt= movridpt_ani;
  }
}

/**
 * Set common pointer functions between mmgs and mmg3d to the matching mmgs
 * functions.
 */
void _MMG5_Set_commonFunc() {
  MMG5_Init_parameters    = _MMG5_Init_parameters;
  _MMG5_bezierCP          = _MMG5_mmgsBezierCP;
  _MMG5_chkmsh            = _MMG5_mmgsChkmsh;
#ifdef USE_SCOTCH
  _MMG5_renumbering       = _MMG5_mmgsRenumbering;
#endif
}
