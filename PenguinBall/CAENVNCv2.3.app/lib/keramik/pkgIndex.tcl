# pkgIndex.tcl for additional tile pixmap themes.
#
# We don't provide the package if the image subdirectory isn't present,
# or we do not have the right version of Tcl/Tk
#
# To use this automatically within tile, the tile-using application should
# use [tile::availableThemes] and [tile::setTheme keramik]
#
# $Id: pkgIndex.tcl,v 1.5 2006/08/04 09:01:31 patthoyts Exp $

if {![file isdirectory [file join $dir keramik]]} { return }
if {![package vsatisfies [package provide Tcl] 8.4]} { return }

package ifneeded tile::theme::keramik 0.3.4 \
    [list source [file join $dir keramik.tcl]]
