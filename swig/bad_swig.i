/* -*- c++ -*- */

#define BAD_API

%include "gnuradio.i"           // the common stuff

//load generated python docstrings
%include "bad_swig_doc.i"

%{
#include "bad/protection_type.h"
#include "bad/ns_peak_detector.h"
#include "bad/ns_detector.h"
#include "bad/ofdm_sampler.h"
#include "bad/ofdm_coarse_frequency_correction.h"
#include "bad/ofdm_differential_demodulator.h"
#include "bad/frequency_deinterleaver.h"
#include "bad/qpsk_symbol_demapper.h"
#include "bad/ofdm_fine_frequency_correction.h"
#include "bad/ns_moving_sum.h"
#include "bad/select_symbols.h"
#include "bad/block_departitioner.h"
#include "bad/depuncturing.h"
#include "bad/convolutional_decoder.h"
#include "bad/energy_dispersal_descrambler.h"
#include "bad/adapter.h"
#include "bad/ofdm_symbols_selector.h"
#include "bad/cus_selector.h"
#include "bad/time_deinterleaver.h"
%}

%include "bad/protection_type.h"

%include "bad/ns_peak_detector.h"
GR_SWIG_BLOCK_MAGIC2(bad, ns_peak_detector);

%include "bad/ns_detector.h"
GR_SWIG_BLOCK_MAGIC2(bad, ns_detector);

%include "bad/ofdm_sampler.h"
GR_SWIG_BLOCK_MAGIC2(bad, ofdm_sampler);

%include "bad/ofdm_coarse_frequency_correction.h"
GR_SWIG_BLOCK_MAGIC2(bad, ofdm_coarse_frequency_correction);

%include "bad/ofdm_differential_demodulator.h"
GR_SWIG_BLOCK_MAGIC2(bad, ofdm_differential_demodulator);

%include "bad/frequency_deinterleaver.h"
GR_SWIG_BLOCK_MAGIC2(bad, frequency_deinterleaver);

%include "bad/qpsk_symbol_demapper.h"
GR_SWIG_BLOCK_MAGIC2(bad, qpsk_symbol_demapper);

%include "bad/ofdm_fine_frequency_correction.h"
GR_SWIG_BLOCK_MAGIC2(bad, ofdm_fine_frequency_correction);

%include "bad/ns_moving_sum.h"
GR_SWIG_BLOCK_MAGIC2(bad, ns_moving_sum);

%include "bad/select_symbols.h"
GR_SWIG_BLOCK_MAGIC2(bad, select_symbols);

%include "bad/block_departitioner.h"
GR_SWIG_BLOCK_MAGIC2(bad, block_departitioner);

%include "bad/depuncturing.h"
GR_SWIG_BLOCK_MAGIC2(bad, depuncturing);

%include "bad/convolutional_decoder.h"
GR_SWIG_BLOCK_MAGIC2(bad, convolutional_decoder);

%include "bad/energy_dispersal_descrambler.h"
GR_SWIG_BLOCK_MAGIC2(bad, energy_dispersal_descrambler);

%include "bad/ofdm_symbols_selector.h"
GR_SWIG_BLOCK_MAGIC2(bad, ofdm_symbols_selector);

%include "bad/cus_selector.h"
GR_SWIG_BLOCK_MAGIC2(bad, cus_selector);

%include "bad/time_deinterleaver.h"
GR_SWIG_BLOCK_MAGIC2(bad, time_deinterleaver);

%include "bad/adapter.h"
GR_SWIG_BLOCK_MAGIC2_TMPL(bad, adapter_bb, adapter<std::uint8_t, std::uint8_t>);
GR_SWIG_BLOCK_MAGIC2_TMPL(bad, adapter_ss, adapter<std::uint16_t, std::uint16_t>);
GR_SWIG_BLOCK_MAGIC2_TMPL(bad, adapter_ii, adapter<std::uint32_t, std::uint32_t>);
GR_SWIG_BLOCK_MAGIC2_TMPL(bad, adapter_ff, adapter<float, float>);
GR_SWIG_BLOCK_MAGIC2_TMPL(bad, adapter_cc, adapter<gr_complex, gr_complex>);
