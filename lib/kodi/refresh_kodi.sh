DIR=$(dirname $0)
KODI_PVR=$DIR/pvr

BASE_URL=https://raw.githubusercontent.com/xbmc/xbmc/master/
OPTIONS="--insecure"
curl $OPTIONS $BASE_URL/xbmc/cores/VideoPlayer/Interface/Addon/DemuxCrypto.h > $KODI_PVR/DemuxCrypto.h
curl $OPTIONS $BASE_URL/xbmc/cores/VideoPlayer/Interface/Addon/TimingConstants.h > $KODI_PVR/TimingConstants.h
curl $OPTIONS $BASE_URL/xbmc/cores/VideoPlayer/Interface/Addon/DemuxPacket.h > $KODI_PVR/DemuxPacket.h
curl $OPTIONS $BASE_URL/xbmc/addons/kodi-addon-dev-kit/include/kodi/AddonBase.h > $KODI_PVR/AddonBase.h
curl $OPTIONS $BASE_URL/xbmc/addons/kodi-addon-dev-kit/include/kodi/versions.h > $KODI_PVR/versions.h
curl $OPTIONS $BASE_URL/xbmc/addons/kodi-addon-dev-kit/include/kodi/libXBMC_pvr.h > $KODI_PVR/libXBMC_pvr.h
curl $OPTIONS $BASE_URL/xbmc/addons/kodi-addon-dev-kit/include/kodi/libKODI_guilib.h > $KODI_PVR/libKODI_guilib.h
curl $OPTIONS $BASE_URL/xbmc/addons/kodi-addon-dev-kit/include/kodi/libXBMC_addon.h > $KODI_PVR/libXBMC_addon.h
curl $OPTIONS $BASE_URL/xbmc/addons/kodi-addon-dev-kit/include/kodi/xbmc_addon_dll.h > $KODI_PVR/xbmc_addon_dll.h
curl $OPTIONS $BASE_URL/xbmc/addons/kodi-addon-dev-kit/include/kodi/xbmc_addon_types.h > $KODI_PVR/xbmc_addon_types.h
curl $OPTIONS $BASE_URL/xbmc/addons/kodi-addon-dev-kit/include/kodi/xbmc_epg_types.h > $KODI_PVR/xbmc_epg_types.h
curl $OPTIONS $BASE_URL/xbmc/addons/kodi-addon-dev-kit/include/kodi/xbmc_pvr_dll.h > $KODI_PVR/xbmc_pvr_dll.h
curl $OPTIONS $BASE_URL/xbmc/addons/kodi-addon-dev-kit/include/kodi/xbmc_pvr_types.h > $KODI_PVR/xbmc_pvr_types.h
curl $OPTIONS $BASE_URL/xbmc/filesystem/IFileTypes.h > $KODI_PVR/IFileTypes.h
