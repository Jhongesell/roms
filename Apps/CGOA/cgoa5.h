/*
** svn $Id$
*******************************************************************************
** Copyright (c) 2002-2010 The ROMS/TOMS Group
**
**   Licensed under a MIT/X style license
**
**   See License_ROMS.txt
**
*******************************************************************************
**
**  Options for Northeast Pacific (NEP5) simulation
*/
 
/* general */

#define CURVGRID
#define MASKING
#define NONLIN_EOS
#define SOLVE3D
#define SALINITY
#ifdef SOLVE3D
# define SPLINES
#endif
#undef  FLOATS
#define STATIONS
#undef WET_DRY

#undef T_PASSIVE
#ifdef T_PASSIVE
# define ANA_PASSIVE
#endif
 
/* ice */

#ifdef SOLVE3D
# define  ICE_MODEL
# ifdef ICE_MODEL
#  define  ICE_THERMO
#  define  ICE_MK
#  undef   ICE_ALB_EC92
#  undef   ICE_SMOOTH
#  define  ICE_MOMENTUM
#  define  ICE_MOM_BULK
#  define  ICE_EVP
#  define  ICE_ADVECT
#  define  ICE_SMOLAR
#  define  ICE_UPWIND
#  define  ICE_BULK_FLUXES
#  define  ANA_AIOBC
#  define  ANA_HIOBC
#  define  ANA_HSNOBC
# endif
#endif

/* output stuff */
 
#define NO_WRITE_GRID
#undef OUT_DOUBLE
#define RST_SINGLE
#define AVERAGES
#ifdef SOLVE3D
# undef FILTERED
# define AVERAGES_DETIDE
# undef DIAGNOSTICS_TS
#endif
#undef DIAGNOSTICS_UV
 
/* advection, dissipation, pressure grad, etc. */
 
#ifdef SOLVE3D
# define DJ_GRADPS
#endif
 
#define UV_ADV
#define UV_COR
#define UV_SADVECTION
 
#ifdef SOLVE3D
# define TS_U3HADVECTION
# define TS_SVADVECTION
# undef TS_MPDATA
#endif
 
#define UV_VIS2
#define MIX_S_UV
#define VISC_GRID
#define SPONGE

#ifdef SOLVE3D
# define TS_DIF2
# define MIX_GEO_TS
# define DIFF_GRID
#endif
 
 
/* vertical mixing */
 
#ifdef SOLVE3D
# define SOLAR_SOURCE
 
# define LMD_MIXING
# ifdef LMD_MIXING
#  define LMD_RIMIX
#  define LMD_CONVEC
#  define LMD_SKPP
#  define LMD_BKPP
#  define LMD_NONLOCAL
#  define LMD_SHAPIRO
#  undef LMD_DDMIX
# endif
 
# undef GLS_MIXING
# undef MY25_MIXING
#endif
 
/* surface forcing */
 
#ifdef SOLVE3D
# define CORE_FORCING
# define BULK_FLUXES
# undef CCSM_FLUXES
# if defined BULK_FLUXES || defined CCSM_FLUXES
#  define LONGWAVE_OUT
#  define DIURNAL_SRFLUX
#  define EMINUSP
#  undef ANA_SRFLUX
#  undef ALBEDO
#  undef LONGWAVE
# endif
#endif
 
/* surface and side corrections */
 
#ifdef SOLVE3D
# undef SRELAXATION
# undef QCORRECTION
#endif
 
#ifdef SOLVE3D
# undef TCLIMATOLOGY
# undef TCLM_NUDGING
#endif
 
/* point sources (rivers, line sources) */
 
/* Using Runoff instead now */
#ifdef SOLVE3D
#define RUNOFF
!# define UV_PSOURCE
!# define TS_PSOURCE
#endif
 
/* tides */
#define LTIDES
#if defined LTIDES 
# define SSH_TIDES
# define UV_TIDES
# define ADD_FSOBC
# define ADD_M2OBC
# undef RAMP_TIDES
# define TIDES_ASTRO
# undef POT_TIDES
# define UV_LDRAG
# define RDRG_GRID
#else
#define UV_QDRAG
#endif
 
/* Boundary conditions...careful with grid orientation */
 
#define EASTERN_WALL
#define NORTHERN_WALL
#undef WESTERN_WALL
#undef SOUTHERN_WALL
 
#define RADIATION_2D
 
#ifndef NORTHERN_WALL
# define NORTH_FSCHAPMAN
# define NORTH_M2FLATHER
# ifdef SOLVE3D
#  define NORTH_M3RADIATION
#  define NORTH_M3NUDGING
#  define NORTH_TRADIATION
#  define NORTH_TNUDGING
#  define NORTH_MIGRADIENT
# endif
#endif
 
#ifndef WESTERN_WALL
# define WEST_FSCHAPMAN
# define WEST_M2FLATHER
# ifdef SOLVE3D
#  define WEST_M3RADIATION
#  define WEST_M3NUDGING
#  define WEST_TRADIATION
#  define WEST_TNUDGING
#  define WEST_MIGRADIENT
# endif
#endif
 
#ifndef SOUTHERN_WALL
# define SOUTH_FSCHAPMAN
# define SOUTH_M2FLATHER
# ifdef SOLVE3D
#  define SOUTH_M3RADIATION
#  define SOUTH_M3NUDGING
#  define SOUTH_TRADIATION
#  define SOUTH_TNUDGING
#  define SOUTH_MIGRADIENT
# endif
#endif
 
#ifndef EASTERN_WALL
# define EAST_FSCHAPMAN
# define EAST_M2FLATHER
# ifdef SOLVE3D
#  define EAST_M3RADIATION
#  define EAST_M3NUDGING
#  define EAST_TRADIATION
#  define EAST_TNUDGING
#  define EAST_MIGRADIENT
# endif
#endif
 
/* roms quirks */
 
#ifdef SOLVE3D
# define ANA_BSFLUX
# define ANA_BTFLUX
#else
# define ANA_SMFLUX
#endif

/* adding biology */
# undef BIO_GOANPZ        /* Sarah Hinckley's 11 box model */
# if defined BIO_GOANPZ
#   define ANA_BIOLOGY       /* analytical biology initial conditions */
#   define ANA_BPFLUX        /* analytical bottom passive tracers fluxes */
#   define ANA_SPFLUX        /* analytical surface passive tracers fluxes */
#   define DIAPAUSE          /* Enable Neocalanus seasonal vertical migration */
#   define IRON_LIMIT        /* Add iron as passive 11th tracer */
#   undef TCLM_NUDGING      /* Nudging of tracer climatology for iron */
# endif
# undef NEMURO
# if defined NEMURO
#   define ANA_BIOLOGY       /* analytical biology initial conditions */
#   define ANA_BPFLUX        /* analytical bottom passive tracers fluxes */
#   define ANA_SPFLUX        /* analytical surface passive tracers fluxes */
#   define IRON_LIMIT        /* Add iron as passive 11th tracer */
#   define IRON_RELAX
#   define BIO_SEDIMENT
#   define HOLLING_GRAZING
# endif