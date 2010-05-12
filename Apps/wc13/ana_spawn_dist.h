      SUBROUTINE ana_spawn_dist (ng, tile, model)
!
!! svn $Id: ana_grid.h 975 2009-05-05 22:51:13Z kate $
!!======================================================================
!! Copyright (c) 2002-2010 The ROMS/TOMS Group                         !
!!   Licensed under a MIT/X style license                              !
!!   See License_ROMS.txt                                              !
!=======================================================================
!                                                                      !
!  This routine sets model spawn_dist using an analytical expression.  !
!                                                                      !
!  On Output:  stored in mod_grid:                                     !
!                                                                      !
!     spawn_dist   Distance along spawning direction for fish.         !
!                                                                      !
!=======================================================================
!
      USE mod_param
      USE mod_grid
      USE mod_ncparam
!
! Imported variable declarations.
!
      integer, intent(in) :: ng, tile, model

#include "tile.h"
!
      CALL ana_spawn_dist_tile (ng, tile, model,                        &
     &                    LBi, UBi, LBj, UBj,                           &
     &                    IminS, ImaxS, JminS, JmaxS,                   &
     &                    GRID(ng) % spawn_dist)
!
! Set analytical header file name used.
!
#ifdef DISTRIBUTE
      IF (Lanafile) THEN
#else
      IF (Lanafile.and.(tile.eq.0)) THEN
#endif
        ANANAME(48)=__FILE__
      END IF

      RETURN
      END SUBROUTINE ana_spawn_dist
!
!***********************************************************************
      SUBROUTINE ana_spawn_dist_tile (ng, tile, model,                  &
     &                          LBi, UBi, LBj, UBj,                     &
     &                          IminS, ImaxS, JminS, JmaxS,             &
     &                          spawn_dist)
!***********************************************************************
!
      USE mod_param
      USE mod_parallel
      USE mod_scalars
      USE mod_grid
!
#ifdef DISTRIBUTE
      USE distribute_mod, ONLY : mp_reduce
#endif
#ifdef DISTRIBUTE
      USE mp_exchange_mod, ONLY : mp_exchange2d
#endif
!
!  Imported variable declarations.
!
      integer, intent(in) :: ng, tile, model
      integer, intent(in) :: LBi, UBi, LBj, UBj
      integer, intent(in) :: IminS, ImaxS, JminS, JmaxS
!
#ifdef ASSUMED_SHAPE
      real(r8), intent(out) :: spawn_dist(LBi:,LBj:)
#else
      real(r8), intent(out) :: spawn_dist(LBi:UBi,LBj:UBj)
#endif
!
!  Local variable declarations.
!
      integer :: Imin, Imax, Jmin, Jmax
      integer :: i, j

#ifdef DISTRIBUTE
      real(r8), dimension(2) :: buffer
      character (len=3), dimension(2) :: op_handle
#endif
!
#include "set_bounds.h"
!
!-----------------------------------------------------------------------
!
!  Determine I- and J-ranges for computing grid data.  This ranges
!  are special in periodic boundary conditons since periodicity cannot
!  be imposed in the grid coordinates.
!
      IF (WESTERN_EDGE) THEN
        Imin=Istr-1
      ELSE
        Imin=Istr
      END IF
      IF (EASTERN_EDGE) THEN
        Imax=Iend+1
      ELSE
        Imax=Iend
      END IF
      IF (SOUTHERN_EDGE) THEN
        Jmin=Jstr-1
      ELSE
        Jmin=Jstr
      END IF
      IF (NORTHERN_EDGE) THEN
        Jmax=Jend+1
      ELSE
        Jmax=Jend
      END IF

#if defined WC13
!
!  Longshore could be either j or lat.
!
      DO j=Jmin,Jmax
        DO i=Imin,Imax
          spawn_dist(i,j)=GRID(ng) % latr(i,j)
        END DO
      END DO
#endif
#ifdef DISTRIBUTE
      CALL mp_exchange2d (ng, tile, model, 1,                           &
     &                    LBi, UBi, LBj, UBj,                           &
     &                    NghostPoints, .FALSE., .FALSE.,               &
     &                    spawn_dist)
#endif
      RETURN
      END SUBROUTINE ana_spawn_dist_tile
