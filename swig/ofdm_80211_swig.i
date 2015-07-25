/* -*- c++ -*- */

#define OFDM_80211_API

%include "gnuradio.i"			// the common stuff

//load generated python docstrings
%include "ofdm_80211_swig_doc.i"

%{
#include "ofdm_80211/short_match_filter.h"
#include "ofdm_80211/ofdm_sync_short.h"
#include "ofdm_80211/bor.h"
%}

%include "ofdm_80211/short_match_filter.h"
GR_SWIG_BLOCK_MAGIC2(ofdm_80211, short_match_filter);

%include "ofdm_80211/ofdm_sync_short.h"
GR_SWIG_BLOCK_MAGIC2(ofdm_80211, ofdm_sync_short);

%include "ofdm_80211/bor.h"
GR_SWIG_BLOCK_MAGIC2(ofdm_80211, bor);

