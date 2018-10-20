project(kodidepends)

cmake_minimum_required (VERSION 2.6 FATAL_ERROR)
cmake_policy (VERSION 2.6)

#
# Install required headers from kodi depends
configure_file(pvr/AddonBase.h ${CMAKE_BINARY_DIR}/include/kodi/AddonBase.h COPYONLY)
configure_file(pvr/versions.h ${CMAKE_BINARY_DIR}/include/kodi/versions.h COPYONLY)
configure_file(pvr/libXBMC_addon.h ${CMAKE_BINARY_DIR}/include/kodi/libXBMC_addon.h COPYONLY)
configure_file(pvr/libKODI_guilib.h ${CMAKE_BINARY_DIR}/include/kodi/libKODI_guilib.h COPYONLY)
configure_file(pvr/libXBMC_pvr.h ${CMAKE_BINARY_DIR}/include/kodi/libXBMC_pvr.h COPYONLY)
configure_file(pvr/DemuxCrypto.h ${CMAKE_BINARY_DIR}/include/kodi/DemuxCrypto.h COPYONLY)
configure_file(pvr/TimingConstants.h ${CMAKE_BINARY_DIR}/include/kodi/TimingConstants.h COPYONLY)
configure_file(pvr/DemuxPacket.h ${CMAKE_BINARY_DIR}/include/kodi/DemuxPacket.h COPYONLY)
configure_file(pvr/xbmc_addon_dll.h ${CMAKE_BINARY_DIR}/include/kodi/xbmc_addon_dll.h COPYONLY)
configure_file(pvr/xbmc_addon_types.h ${CMAKE_BINARY_DIR}/include/kodi/xbmc_addon_types.h COPYONLY)
configure_file(pvr/xbmc_epg_types.h ${CMAKE_BINARY_DIR}/include/kodi/xbmc_epg_types.h COPYONLY)
configure_file(pvr/xbmc_pvr_dll.h ${CMAKE_BINARY_DIR}/include/kodi/xbmc_pvr_dll.h COPYONLY)
configure_file(pvr/xbmc_pvr_types.h ${CMAKE_BINARY_DIR}/include/kodi/xbmc_pvr_types.h COPYONLY)
configure_file(pvr/IFileTypes.h ${CMAKE_BINARY_DIR}/include/kodi/IFileTypes.h COPYONLY)

