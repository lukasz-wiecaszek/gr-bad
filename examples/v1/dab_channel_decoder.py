#!/usr/bin/env python3
# -*- coding: utf-8 -*-

#
# SPDX-License-Identifier: GPL-3.0
#
# GNU Radio Python Flow Graph
# Title: DAB channel  decoder
# Author: Łukasz Więcaszek
# GNU Radio version: 3.8.1.0

from distutils.version import StrictVersion

if __name__ == '__main__':
    import ctypes
    import sys
    if sys.platform.startswith('linux'):
        try:
            x11 = ctypes.cdll.LoadLibrary('libX11.so')
            x11.XInitThreads()
        except:
            print("Warning: failed to XInitThreads()")

from PyQt5 import Qt
from gnuradio import qtgui
from gnuradio.filter import firdes
import sip
from gnuradio import blocks
from gnuradio import fft
from gnuradio.fft import window
from gnuradio import gr
import sys
import signal
from argparse import ArgumentParser
from gnuradio.eng_arg import eng_float, intx
from gnuradio import eng_notation
from gnuradio.qtgui import Range, RangeWidget
import bad
import osmosdr
import time

from gnuradio import qtgui

class dab_channel_decoder(gr.top_block, Qt.QWidget):

    def __init__(self):
        gr.top_block.__init__(self, "DAB channel  decoder")
        Qt.QWidget.__init__(self)
        self.setWindowTitle("DAB channel  decoder")
        qtgui.util.check_set_qss()
        try:
            self.setWindowIcon(Qt.QIcon.fromTheme('gnuradio-grc'))
        except:
            pass
        self.top_scroll_layout = Qt.QVBoxLayout()
        self.setLayout(self.top_scroll_layout)
        self.top_scroll = Qt.QScrollArea()
        self.top_scroll.setFrameStyle(Qt.QFrame.NoFrame)
        self.top_scroll_layout.addWidget(self.top_scroll)
        self.top_scroll.setWidgetResizable(True)
        self.top_widget = Qt.QWidget()
        self.top_scroll.setWidget(self.top_widget)
        self.top_layout = Qt.QVBoxLayout(self.top_widget)
        self.top_grid_layout = Qt.QGridLayout()
        self.top_layout.addLayout(self.top_grid_layout)

        self.settings = Qt.QSettings("GNU Radio", "dab_channel_decoder")

        try:
            if StrictVersion(Qt.qVersion()) < StrictVersion("5.0.0"):
                self.restoreGeometry(self.settings.value("geometry").toByteArray())
            else:
                self.restoreGeometry(self.settings.value("geometry"))
        except:
            pass

        ##################################################
        # Variables
        ##################################################
        self.samp_rate = samp_rate = 2048000
        self.freq_offset = freq_offset = 0

        ##################################################
        # Blocks
        ##################################################
        self.rtlsdr_source_0_0 = osmosdr.source(
            args="numchan=" + str(1) + " " + ''
        )
        self.rtlsdr_source_0_0.set_time_unknown_pps(osmosdr.time_spec_t())
        self.rtlsdr_source_0_0.set_sample_rate(samp_rate)
        self.rtlsdr_source_0_0.set_center_freq(218640000, 0)
        self.rtlsdr_source_0_0.set_freq_corr(0, 0)
        self.rtlsdr_source_0_0.set_gain(30, 0)
        self.rtlsdr_source_0_0.set_if_gain(20, 0)
        self.rtlsdr_source_0_0.set_bb_gain(20, 0)
        self.rtlsdr_source_0_0.set_antenna('', 0)
        self.rtlsdr_source_0_0.set_bandwidth(0, 0)
        self.qtgui_time_sink_x_1_0 = qtgui.time_sink_f(
            2048*96*2, #size
            samp_rate, #samp_rate
            "", #name
            1 #number of inputs
        )
        self.qtgui_time_sink_x_1_0.set_update_time(0.10)
        self.qtgui_time_sink_x_1_0.set_y_axis(-1  * 3.1415 / 2048, 1 * 3.1415 / 2048)

        self.qtgui_time_sink_x_1_0.set_y_label('Amplitude', "")

        self.qtgui_time_sink_x_1_0.enable_tags(True)
        self.qtgui_time_sink_x_1_0.set_trigger_mode(qtgui.TRIG_MODE_FREE, qtgui.TRIG_SLOPE_POS, 0.0, 0, 0, "")
        self.qtgui_time_sink_x_1_0.enable_autoscale(False)
        self.qtgui_time_sink_x_1_0.enable_grid(False)
        self.qtgui_time_sink_x_1_0.enable_axis_labels(True)
        self.qtgui_time_sink_x_1_0.enable_control_panel(False)
        self.qtgui_time_sink_x_1_0.enable_stem_plot(False)


        labels = ['Signal 1', 'Signal 2', 'Signal 3', 'Signal 4', 'Signal 5',
            'Signal 6', 'Signal 7', 'Signal 8', 'Signal 9', 'Signal 10']
        widths = [1, 1, 1, 1, 1,
            1, 1, 1, 1, 1]
        colors = ['blue', 'red', 'green', 'black', 'cyan',
            'magenta', 'yellow', 'dark red', 'dark green', 'dark blue']
        alphas = [1.0, 1.0, 1.0, 1.0, 1.0,
            1.0, 1.0, 1.0, 1.0, 1.0]
        styles = [1, 1, 1, 1, 1,
            1, 1, 1, 1, 1]
        markers = [-1, -1, -1, -1, -1,
            -1, -1, -1, -1, -1]


        for i in range(1):
            if len(labels[i]) == 0:
                self.qtgui_time_sink_x_1_0.set_line_label(i, "Data {0}".format(i))
            else:
                self.qtgui_time_sink_x_1_0.set_line_label(i, labels[i])
            self.qtgui_time_sink_x_1_0.set_line_width(i, widths[i])
            self.qtgui_time_sink_x_1_0.set_line_color(i, colors[i])
            self.qtgui_time_sink_x_1_0.set_line_style(i, styles[i])
            self.qtgui_time_sink_x_1_0.set_line_marker(i, markers[i])
            self.qtgui_time_sink_x_1_0.set_line_alpha(i, alphas[i])

        self._qtgui_time_sink_x_1_0_win = sip.wrapinstance(self.qtgui_time_sink_x_1_0.pyqwidget(), Qt.QWidget)
        self.top_grid_layout.addWidget(self._qtgui_time_sink_x_1_0_win)
        self.qtgui_time_sink_x_1 = qtgui.time_sink_f(
            2048*5, #size
            samp_rate, #samp_rate
            "", #name
            1 #number of inputs
        )
        self.qtgui_time_sink_x_1.set_update_time(0.10)
        self.qtgui_time_sink_x_1.set_y_axis(-1, 1)

        self.qtgui_time_sink_x_1.set_y_label('Amplitude', "")

        self.qtgui_time_sink_x_1.enable_tags(True)
        self.qtgui_time_sink_x_1.set_trigger_mode(qtgui.TRIG_MODE_FREE, qtgui.TRIG_SLOPE_POS, 0.0, 0, 0, "")
        self.qtgui_time_sink_x_1.enable_autoscale(True)
        self.qtgui_time_sink_x_1.enable_grid(False)
        self.qtgui_time_sink_x_1.enable_axis_labels(True)
        self.qtgui_time_sink_x_1.enable_control_panel(False)
        self.qtgui_time_sink_x_1.enable_stem_plot(False)


        labels = ['Signal 1', 'Signal 2', 'Signal 3', 'Signal 4', 'Signal 5',
            'Signal 6', 'Signal 7', 'Signal 8', 'Signal 9', 'Signal 10']
        widths = [1, 1, 1, 1, 1,
            1, 1, 1, 1, 1]
        colors = ['blue', 'red', 'green', 'black', 'cyan',
            'magenta', 'yellow', 'dark red', 'dark green', 'dark blue']
        alphas = [1.0, 1.0, 1.0, 1.0, 1.0,
            1.0, 1.0, 1.0, 1.0, 1.0]
        styles = [1, 1, 1, 1, 1,
            1, 1, 1, 1, 1]
        markers = [-1, -1, -1, -1, -1,
            -1, -1, -1, -1, -1]


        for i in range(1):
            if len(labels[i]) == 0:
                self.qtgui_time_sink_x_1.set_line_label(i, "Data {0}".format(i))
            else:
                self.qtgui_time_sink_x_1.set_line_label(i, labels[i])
            self.qtgui_time_sink_x_1.set_line_width(i, widths[i])
            self.qtgui_time_sink_x_1.set_line_color(i, colors[i])
            self.qtgui_time_sink_x_1.set_line_style(i, styles[i])
            self.qtgui_time_sink_x_1.set_line_marker(i, markers[i])
            self.qtgui_time_sink_x_1.set_line_alpha(i, alphas[i])

        self._qtgui_time_sink_x_1_win = sip.wrapinstance(self.qtgui_time_sink_x_1.pyqwidget(), Qt.QWidget)
        self.top_grid_layout.addWidget(self._qtgui_time_sink_x_1_win)
        self.qtgui_freq_sink_x_0 = qtgui.freq_sink_c(
            2048, #size
            firdes.WIN_BLACKMAN_hARRIS, #wintype
            0, #fc
            samp_rate, #bw
            "", #name
            1
        )
        self.qtgui_freq_sink_x_0.set_update_time(0.10)
        self.qtgui_freq_sink_x_0.set_y_axis(-140, 10)
        self.qtgui_freq_sink_x_0.set_y_label('Relative Gain', 'dB')
        self.qtgui_freq_sink_x_0.set_trigger_mode(qtgui.TRIG_MODE_FREE, 0.0, 0, "")
        self.qtgui_freq_sink_x_0.enable_autoscale(False)
        self.qtgui_freq_sink_x_0.enable_grid(False)
        self.qtgui_freq_sink_x_0.set_fft_average(1.0)
        self.qtgui_freq_sink_x_0.enable_axis_labels(True)
        self.qtgui_freq_sink_x_0.enable_control_panel(False)



        labels = ['', '', '', '', '',
            '', '', '', '', '']
        widths = [1, 1, 1, 1, 1,
            1, 1, 1, 1, 1]
        colors = ["blue", "red", "green", "black", "cyan",
            "magenta", "yellow", "dark red", "dark green", "dark blue"]
        alphas = [1.0, 1.0, 1.0, 1.0, 1.0,
            1.0, 1.0, 1.0, 1.0, 1.0]

        for i in range(1):
            if len(labels[i]) == 0:
                self.qtgui_freq_sink_x_0.set_line_label(i, "Data {0}".format(i))
            else:
                self.qtgui_freq_sink_x_0.set_line_label(i, labels[i])
            self.qtgui_freq_sink_x_0.set_line_width(i, widths[i])
            self.qtgui_freq_sink_x_0.set_line_color(i, colors[i])
            self.qtgui_freq_sink_x_0.set_line_alpha(i, alphas[i])

        self._qtgui_freq_sink_x_0_win = sip.wrapinstance(self.qtgui_freq_sink_x_0.pyqwidget(), Qt.QWidget)
        self.top_grid_layout.addWidget(self._qtgui_freq_sink_x_0_win)
        self.qtgui_const_sink_x_1 = qtgui.const_sink_c(
            1024, #size
            "", #name
            1 #number of inputs
        )
        self.qtgui_const_sink_x_1.set_update_time(0.10)
        self.qtgui_const_sink_x_1.set_y_axis(-200, 200)
        self.qtgui_const_sink_x_1.set_x_axis(-200, 200)
        self.qtgui_const_sink_x_1.set_trigger_mode(qtgui.TRIG_MODE_FREE, qtgui.TRIG_SLOPE_POS, 0.0, 0, "")
        self.qtgui_const_sink_x_1.enable_autoscale(False)
        self.qtgui_const_sink_x_1.enable_grid(False)
        self.qtgui_const_sink_x_1.enable_axis_labels(True)


        labels = ['', '', '', '', '',
            '', '', '', '', '']
        widths = [1, 1, 1, 1, 1,
            1, 1, 1, 1, 1]
        colors = ["blue", "red", "red", "red", "red",
            "red", "red", "red", "red", "red"]
        styles = [0, 0, 0, 0, 0,
            0, 0, 0, 0, 0]
        markers = [0, 0, 0, 0, 0,
            0, 0, 0, 0, 0]
        alphas = [1.0, 1.0, 1.0, 1.0, 1.0,
            1.0, 1.0, 1.0, 1.0, 1.0]

        for i in range(1):
            if len(labels[i]) == 0:
                self.qtgui_const_sink_x_1.set_line_label(i, "Data {0}".format(i))
            else:
                self.qtgui_const_sink_x_1.set_line_label(i, labels[i])
            self.qtgui_const_sink_x_1.set_line_width(i, widths[i])
            self.qtgui_const_sink_x_1.set_line_color(i, colors[i])
            self.qtgui_const_sink_x_1.set_line_style(i, styles[i])
            self.qtgui_const_sink_x_1.set_line_marker(i, markers[i])
            self.qtgui_const_sink_x_1.set_line_alpha(i, alphas[i])

        self._qtgui_const_sink_x_1_win = sip.wrapinstance(self.qtgui_const_sink_x_1.pyqwidget(), Qt.QWidget)
        self.top_grid_layout.addWidget(self._qtgui_const_sink_x_1_win)
        self._freq_offset_range = Range(-1000, +1000, 10, 0, 200)
        self._freq_offset_win = RangeWidget(self._freq_offset_range, self.set_freq_offset, 'freq_offset', "counter_slider", float)
        self.top_grid_layout.addWidget(self._freq_offset_win)
        self.fft_vxx_0 = fft.fft_vcc(2048, True, [], True, 1)
        self.blocks_vector_to_stream_0_0_0_1 = blocks.vector_to_stream(gr.sizeof_char*1, 2304)
        self.blocks_vector_to_stream_0_0_0 = blocks.vector_to_stream(gr.sizeof_char*1, 768)
        self.blocks_vector_to_stream_0_0 = blocks.vector_to_stream(gr.sizeof_gr_complex*1, 2048)
        self.blocks_vector_to_stream_0 = blocks.vector_to_stream(gr.sizeof_gr_complex*1, 1536)
        self.blocks_unpacked_to_packed_xx_0_0_0 = blocks.unpacked_to_packed_bb(1, gr.GR_MSB_FIRST)
        self.blocks_unpacked_to_packed_xx_0 = blocks.unpacked_to_packed_bb(1, gr.GR_MSB_FIRST)
        self.blocks_file_sink_0_0_0 = blocks.file_sink(gr.sizeof_char*1, 'msc.fifo', False)
        self.blocks_file_sink_0_0_0.set_unbuffered(False)
        self.blocks_file_sink_0 = blocks.file_sink(gr.sizeof_char*1, 'fic.dat', False)
        self.blocks_file_sink_0.set_unbuffered(False)
        self.blocks_complex_to_mag_squared_0 = blocks.complex_to_mag_squared(1)
        self.bad_time_deinterleaver_0 = bad.time_deinterleaver(4608)
        self.bad_qpsk_symbol_demapper_0 = bad.qpsk_symbol_demapper()
        self.bad_ofdm_symbols_selector_0_0 = bad.ofdm_symbols_selector(4, 72)
        self.bad_ofdm_symbols_selector_0 = bad.ofdm_symbols_selector(1, 3)
        self.bad_ofdm_sampler_0 = bad.ofdm_sampler()
        self.bad_ofdm_fine_frequency_correction_0 = bad.ofdm_fine_frequency_correction(0.1)
        self.bad_ofdm_differential_demodulator_0 = bad.ofdm_differential_demodulator()
        self.bad_ofdm_coarse_frequency_correction_0 = bad.ofdm_coarse_frequency_correction()
        self.bad_ns_detector_1 = bad.ns_detector()
        self.bad_msc_eep_convolutional_decoder_0 = bad.convolutional_decoder(bad.PROTECTION_TYPE_EEP_A, 3, 12)
        self.bad_frequency_deinterleaver_0 = bad.frequency_deinterleaver()
        self.bad_fic_convolutional_decoder_0 = bad.convolutional_decoder(bad.PROTECTION_TYPE_FIC, 0, 0)
        self.bad_energy_dispersal_descrambler_0_0 = bad.energy_dispersal_descrambler(2304)
        self.bad_energy_dispersal_descrambler_0 = bad.energy_dispersal_descrambler(768)
        self.bad_cus_selector_0 = bad.cus_selector(618, 72)
        self.bad_adapter_0_1 = bad.adapter_ff(64, 72, 64 * 72, 1, "")
        self.bad_adapter_0_0 = bad.adapter_ff(3072, 3, 2304, 4, "")
        self.bad_adapter_0 = bad.adapter_ff(3072, 18, 64, 864, "cu")



        ##################################################
        # Connections
        ##################################################
        self.connect((self.bad_adapter_0, 0), (self.bad_cus_selector_0, 0))
        self.connect((self.bad_adapter_0_0, 0), (self.bad_fic_convolutional_decoder_0, 0))
        self.connect((self.bad_adapter_0_1, 0), (self.bad_time_deinterleaver_0, 0))
        self.connect((self.bad_cus_selector_0, 0), (self.bad_adapter_0_1, 0))
        self.connect((self.bad_energy_dispersal_descrambler_0, 0), (self.blocks_vector_to_stream_0_0_0, 0))
        self.connect((self.bad_energy_dispersal_descrambler_0_0, 0), (self.blocks_vector_to_stream_0_0_0_1, 0))
        self.connect((self.bad_fic_convolutional_decoder_0, 0), (self.bad_energy_dispersal_descrambler_0, 0))
        self.connect((self.bad_frequency_deinterleaver_0, 0), (self.bad_qpsk_symbol_demapper_0, 0))
        self.connect((self.bad_msc_eep_convolutional_decoder_0, 0), (self.bad_energy_dispersal_descrambler_0_0, 0))
        self.connect((self.bad_ns_detector_1, 0), (self.bad_ofdm_fine_frequency_correction_0, 0))
        self.connect((self.bad_ofdm_coarse_frequency_correction_0, 0), (self.bad_ofdm_differential_demodulator_0, 0))
        self.connect((self.bad_ofdm_differential_demodulator_0, 0), (self.bad_frequency_deinterleaver_0, 0))
        self.connect((self.bad_ofdm_differential_demodulator_0, 0), (self.blocks_vector_to_stream_0, 0))
        self.connect((self.bad_ofdm_fine_frequency_correction_0, 0), (self.bad_ofdm_sampler_0, 0))
        self.connect((self.bad_ofdm_fine_frequency_correction_0, 1), (self.qtgui_time_sink_x_1_0, 0))
        self.connect((self.bad_ofdm_sampler_0, 0), (self.fft_vxx_0, 0))
        self.connect((self.bad_ofdm_symbols_selector_0, 0), (self.bad_adapter_0_0, 0))
        self.connect((self.bad_ofdm_symbols_selector_0_0, 0), (self.bad_adapter_0, 0))
        self.connect((self.bad_qpsk_symbol_demapper_0, 0), (self.bad_ofdm_symbols_selector_0, 0))
        self.connect((self.bad_qpsk_symbol_demapper_0, 0), (self.bad_ofdm_symbols_selector_0_0, 0))
        self.connect((self.bad_time_deinterleaver_0, 0), (self.bad_msc_eep_convolutional_decoder_0, 0))
        self.connect((self.blocks_complex_to_mag_squared_0, 0), (self.qtgui_time_sink_x_1, 0))
        self.connect((self.blocks_unpacked_to_packed_xx_0, 0), (self.blocks_file_sink_0, 0))
        self.connect((self.blocks_unpacked_to_packed_xx_0_0_0, 0), (self.blocks_file_sink_0_0_0, 0))
        self.connect((self.blocks_vector_to_stream_0, 0), (self.qtgui_const_sink_x_1, 0))
        self.connect((self.blocks_vector_to_stream_0_0, 0), (self.blocks_complex_to_mag_squared_0, 0))
        self.connect((self.blocks_vector_to_stream_0_0_0, 0), (self.blocks_unpacked_to_packed_xx_0, 0))
        self.connect((self.blocks_vector_to_stream_0_0_0_1, 0), (self.blocks_unpacked_to_packed_xx_0_0_0, 0))
        self.connect((self.fft_vxx_0, 0), (self.bad_ofdm_coarse_frequency_correction_0, 0))
        self.connect((self.fft_vxx_0, 0), (self.blocks_vector_to_stream_0_0, 0))
        self.connect((self.rtlsdr_source_0_0, 0), (self.bad_ns_detector_1, 0))
        self.connect((self.rtlsdr_source_0_0, 0), (self.qtgui_freq_sink_x_0, 0))


    def closeEvent(self, event):
        self.settings = Qt.QSettings("GNU Radio", "dab_channel_decoder")
        self.settings.setValue("geometry", self.saveGeometry())
        event.accept()

    def get_samp_rate(self):
        return self.samp_rate

    def set_samp_rate(self, samp_rate):
        self.samp_rate = samp_rate
        self.qtgui_freq_sink_x_0.set_frequency_range(0, self.samp_rate)
        self.qtgui_time_sink_x_1.set_samp_rate(self.samp_rate)
        self.qtgui_time_sink_x_1_0.set_samp_rate(self.samp_rate)
        self.rtlsdr_source_0_0.set_sample_rate(self.samp_rate)

    def get_freq_offset(self):
        return self.freq_offset

    def set_freq_offset(self, freq_offset):
        self.freq_offset = freq_offset





def main(top_block_cls=dab_channel_decoder, options=None):

    if StrictVersion("4.5.0") <= StrictVersion(Qt.qVersion()) < StrictVersion("5.0.0"):
        style = gr.prefs().get_string('qtgui', 'style', 'raster')
        Qt.QApplication.setGraphicsSystem(style)
    qapp = Qt.QApplication(sys.argv)

    tb = top_block_cls()

    tb.start()

    tb.show()

    def sig_handler(sig=None, frame=None):
        Qt.QApplication.quit()

    signal.signal(signal.SIGINT, sig_handler)
    signal.signal(signal.SIGTERM, sig_handler)

    timer = Qt.QTimer()
    timer.start(500)
    timer.timeout.connect(lambda: None)

    def quitting():
        tb.stop()
        tb.wait()

    qapp.aboutToQuit.connect(quitting)
    qapp.exec_()

if __name__ == '__main__':
    main()
