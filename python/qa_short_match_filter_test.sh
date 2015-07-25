#!/bin/sh
export VOLK_GENERIC=1
export GR_DONT_LOAD_PREFS=1
export srcdir=/home/juan/Cognitivegnublocks/gr-ofdm_80211/python
export PATH=/home/juan/Cognitivegnublocks/gr-ofdm_80211/python:$PATH
export LD_LIBRARY_PATH=/home/juan/Cognitivegnublocks/gr-ofdm_80211/lib:$LD_LIBRARY_PATH
export PYTHONPATH=/home/juan/Cognitivegnublocks/gr-ofdm_80211/swig:$PYTHONPATH
/usr/bin/python /home/juan/Cognitivegnublocks/gr-ofdm_80211/python/qa_short_match_filter.py 
