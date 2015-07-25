#!/bin/sh
export VOLK_GENERIC=1
export GR_DONT_LOAD_PREFS=1
export srcdir=/home/juan/Cognitivegnublocks/gr-ofdm_80211/lib
export PATH=/home/juan/Cognitivegnublocks/gr-ofdm_80211/lib:$PATH
export LD_LIBRARY_PATH=/home/juan/Cognitivegnublocks/gr-ofdm_80211/lib:$LD_LIBRARY_PATH
export PYTHONPATH=$PYTHONPATH
test-ofdm_80211 
