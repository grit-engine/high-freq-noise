# Copyright (c) David Cunningham and the Grit Game Engine project 2012
# Licensed under the MIT license: http://www.opensource.org/licenses/mit-license.php

TARGETS=HiFreqNoiseRing.64.bmp HiFreqNoiseDisc.64.bmp HiFreqNoiseGauss.64.bmp WhiteNoiseRing.64.bmp WhiteNoiseDisc.64.bmp WhiteNoiseGauss.64.bmp HiFreqNoiseRing.32.bmp HiFreqNoiseDisc.32.bmp HiFreqNoiseGauss.32.bmp WhiteNoiseRing.32.bmp WhiteNoiseDisc.32.bmp WhiteNoiseGauss.32.bmp

all: $(TARGETS)

install:
	cp $(TARGETS) ../grit_core/media/system

high_freq_noise: high_freq_noise.c++
	devg++ $< -o $@


HiFreqNoiseRing.64.pnm: high_freq_noise
	WIDTH=64 HEIGHT=64 RING=1 ./high_freq_noise
	mv HiFreqNoise.pnm $@
	
HiFreqNoiseDisc.64.pnm: high_freq_noise
	WIDTH=64 HEIGHT=64 ./high_freq_noise
	mv HiFreqNoise.pnm $@
	
HiFreqNoiseGauss.64.pnm: high_freq_noise
	WIDTH=64 HEIGHT=64 GAUSS=1 ./high_freq_noise
	mv HiFreqNoise.pnm $@
	
WhiteNoiseRing.64.pnm: high_freq_noise
	WIDTH=64 HEIGHT=64 WHITE=1 RING=1 ./high_freq_noise
	mv HiFreqNoise.pnm $@
	
WhiteNoiseDisc.64.pnm: high_freq_noise
	WIDTH=64 HEIGHT=64 WHITE=1 ./high_freq_noise
	mv HiFreqNoise.pnm $@
	
WhiteNoiseGauss.64.pnm: high_freq_noise
	WIDTH=64 HEIGHT=64 WHITE=1 GAUSS=1 ./high_freq_noise
	mv HiFreqNoise.pnm $@

HiFreqNoiseRing.32.pnm: high_freq_noise
	WIDTH=32 HEIGHT=32 RING=1 ./high_freq_noise
	mv HiFreqNoise.pnm $@
	
HiFreqNoiseDisc.32.pnm: high_freq_noise
	WIDTH=32 HEIGHT=32 ./high_freq_noise
	mv HiFreqNoise.pnm $@
	
HiFreqNoiseGauss.32.pnm: high_freq_noise
	WIDTH=32 HEIGHT=32 GAUSS=1 ./high_freq_noise
	mv HiFreqNoise.pnm $@
	
WhiteNoiseRing.32.pnm: high_freq_noise
	WIDTH=32 HEIGHT=32 WHITE=1 RING=1 ./high_freq_noise
	mv HiFreqNoise.pnm $@
	
WhiteNoiseDisc.32.pnm: high_freq_noise
	WIDTH=32 HEIGHT=32 WHITE=1 ./high_freq_noise
	mv HiFreqNoise.pnm $@
	
WhiteNoiseGauss.32.pnm: high_freq_noise
	WIDTH=32 HEIGHT=32 WHITE=1 GAUSS=1 ./high_freq_noise
	mv HiFreqNoise.pnm $@

	
%.bmp: %.pnm
	ppmtobmp $< > $@
