#!/bin/bash

# clear image directory
# rm scaled/*

indexfile="../Source/gui/UIAssetsIndices.h"
datafile="../Source/gui/UIAssetsData.cpp"
datafileheader="../Source/gui/UIAssetsData.h"
sizefile="../Source/gui/UIAssetsSize.cpp"
sizefileheader="../Source/gui/UIAssetsSize.h"
cmakefile="./CMakeLists.txt"

# count number of png files in this dir
numfiles=$(find -name "*.png" -not -path "./12/*" 2>/dev/null | wc -l)
echo "Processing $numfiles PNG images"

rm "$indexfile"
rm "$cmakefile"
rm "$datafile"
rm "$sizefile"
rm "$datafileheader"
rm "$sizefileheader"

echo "//! This file is autogenerated by assets/graphics/create_graphics_headers.sh" >> "$indexfile"
echo "//! Do not edit this by hand" >> "$indexfile"
echo "" >> "$indexfile"
echo "#pragma once" >> "$indexfile"
echo "" >> "$indexfile"
echo "namespace UIAssets {" >> "$indexfile"
echo "" >> "$indexfile"
echo "enum class Indices : int {" >> "$indexfile"

echo "//! This file is autogenerated by assets/graphics/create_graphics_headers.sh" >> "$datafileheader"
echo "//! Do not edit this by hand" >> "$datafileheader"
echo "" >> "$datafileheader"
echo "#pragma once" >> "$datafileheader"
echo "" >> "$datafileheader"
echo "#include \"../GlobalIncludes.h\"" >> "$datafileheader"
echo "" >> "$datafileheader"
echo "struct UIAssetsData {" >> "$datafileheader"
echo "    static std::array<const char*, $numfiles> Data;" >> "$datafileheader"
echo "};" >> "$datafileheader"

echo "//! This file is autogenerated by assets/graphics/create_graphics_headers.sh" >> "$datafile"
echo "//! Do not edit this by hand" >> "$datafile"
echo "" >> "$datafile"
echo "#include \"UIAssetsData.h\"" >> "$datafile"
echo "" >> "$datafile"
echo "std::array<const char*, $numfiles> UIAssetsData::Data = {" >> "$datafile"


echo "//! This file is autogenerated by assets/graphics/create_graphics_headers.sh" >> "$sizefileheader"
echo "//! Do not edit this by hand" >> "$sizefileheader"
echo "" >> "$sizefileheader"
echo "#pragma once" >> "$sizefileheader"
echo "" >> "$sizefileheader"
echo "#include \"../GlobalIncludes.h\"" >> "$sizefileheader"
echo "struct UIAssetsSize {" >> "$sizefileheader"
echo "    static std::array<size_t, $numfiles> Size;" >> "$sizefileheader"
echo "};" >> "$sizefileheader"

echo "//! This file is autogenerated by assets/graphics/create_graphics_headers.sh" >> "$sizefile"
echo "//! Do not edit this by hand" >> "$sizefile"
echo "" >> "$sizefile"
echo "#include \"UIAssetsSize.h\"" >> "$sizefile"
echo "" >> "$sizefile"
echo "std::array<size_t, $numfiles> UIAssetsSize::Size = {" >> "$sizefile"



echo "#! This file is autogenerated by assets/graphics/create_graphics_headers.sh" >> "$cmakefile"
echo "#! Do not edit this by hand" >> "$cmakefile"
echo "" >> "$cmakefile"
echo "juce_add_binary_data(Odin2_BinaryData" >> $cmakefile
echo "SOURCES" >> $cmakefile
echo "    \"GuiData.json\"" >> "$cmakefile"
echo "    \"Soundbanks/Factory Presets/Arps & Sequences/Arp Charger [RM].odin\"" >> "$cmakefile"
echo "    \"Soundbanks/Factory Presets/Arps & Sequences/Arp Chopper [RM].odin\"" >> "$cmakefile"
echo "    \"Soundbanks/Factory Presets/Arps & Sequences/Bass Arp 1 [RS].odin\"" >> "$cmakefile"
echo "    \"Soundbanks/Factory Presets/Arps & Sequences/Bassline.odin\"" >> "$cmakefile"
echo "    \"Soundbanks/Factory Presets/Arps & Sequences/Cinedrive (MW) [Photonic].odin\"" >> "$cmakefile"
echo "    \"Soundbanks/Factory Presets/Arps & Sequences/Critical [tx].odin\"" >> "$cmakefile"
echo "    \"Soundbanks/Factory Presets/Arps & Sequences/Darkness [psylion].odin\"" >> "$cmakefile"
echo "    \"Soundbanks/Factory Presets/Arps & Sequences/Doctor Karlsson.odin\"" >> "$cmakefile"
echo "    \"Soundbanks/Factory Presets/Arps & Sequences/Dreamy ARP [psylion].odin\"" >> "$cmakefile"
echo "    \"Soundbanks/Factory Presets/Arps & Sequences/Forgive me GOD.odin\"" >> "$cmakefile"
echo "    \"Soundbanks/Factory Presets/Arps & Sequences/Funk Acid 2 [psylion].odin\"" >> "$cmakefile"
echo "    \"Soundbanks/Factory Presets/Arps & Sequences/Funk Acid [psylion].odin\"" >> "$cmakefile"
echo "    \"Soundbanks/Factory Presets/Arps & Sequences/Funny 2.odin\"" >> "$cmakefile"
echo "    \"Soundbanks/Factory Presets/Arps & Sequences/Glass Morph ARP [RS].odin\"" >> "$cmakefile"
echo "    \"Soundbanks/Factory Presets/Arps & Sequences/Harpstrum Down [RS].odin\"" >> "$cmakefile"
echo "    \"Soundbanks/Factory Presets/Arps & Sequences/Harpstrum Up [RS].odin\"" >> "$cmakefile"
echo "    \"Soundbanks/Factory Presets/Arps & Sequences/I was born in 90s [psylion].odin\"" >> "$cmakefile"
echo "    \"Soundbanks/Factory Presets/Arps & Sequences/Midi Rain.odin\"" >> "$cmakefile"
echo "    \"Soundbanks/Factory Presets/Arps & Sequences/Minor Song.odin\"" >> "$cmakefile"
echo "    \"Soundbanks/Factory Presets/Arps & Sequences/Modular Mess 2.odin\"" >> "$cmakefile"
echo "    \"Soundbanks/Factory Presets/Arps & Sequences/Omani Desert 1 [psylion].odin\"" >> "$cmakefile"
echo "    \"Soundbanks/Factory Presets/Arps & Sequences/Omani Desert 2 [psylion].odin\"" >> "$cmakefile"
echo "    \"Soundbanks/Factory Presets/Arps & Sequences/RandArpChords (MW) [Photonic].odin\"" >> "$cmakefile"
echo "    \"Soundbanks/Factory Presets/Arps & Sequences/Self Phasing Arp.odin\"" >> "$cmakefile"
echo "    \"Soundbanks/Factory Presets/Arps & Sequences/Sharp Lead.odin\"" >> "$cmakefile"
echo "    \"Soundbanks/Factory Presets/Arps & Sequences/Sound of Paradise [psylion].odin\"" >> "$cmakefile"
echo "    \"Soundbanks/Factory Presets/Arps & Sequences/The Arp 2.0 [XR].odin\"" >> "$cmakefile"
echo "    \"Soundbanks/Factory Presets/Atmospheres/Alien Atmo [tx].odin\"" >> "$cmakefile"
echo "    \"Soundbanks/Factory Presets/Atmospheres/Alien Chaos [psylion].odin\"" >> "$cmakefile"
echo "    \"Soundbanks/Factory Presets/Atmospheres/Alien Chaos2 [psylion].odin\"" >> "$cmakefile"
echo "    \"Soundbanks/Factory Presets/Atmospheres/Analog Particles [XR].odin\"" >> "$cmakefile"
echo "    \"Soundbanks/Factory Presets/Atmospheres/Antarctica [RS].odin\"" >> "$cmakefile"
echo "    \"Soundbanks/Factory Presets/Atmospheres/Atmo-Chaos [Photonic].odin\"" >> "$cmakefile"
echo "    \"Soundbanks/Factory Presets/Atmospheres/Blinking Pad [Photonic].odin\"" >> "$cmakefile"
echo "    \"Soundbanks/Factory Presets/Atmospheres/Digital Motion [XR].odin\"" >> "$cmakefile"
echo "    \"Soundbanks/Factory Presets/Atmospheres/Dreams of Utopia [psylion].odin\"" >> "$cmakefile"
echo "    \"Soundbanks/Factory Presets/Atmospheres/Eerie Pad.odin\"" >> "$cmakefile"
echo "    \"Soundbanks/Factory Presets/Atmospheres/Expressive Atmosphere [XR].odin\"" >> "$cmakefile"
echo "    \"Soundbanks/Factory Presets/Atmospheres/Floating Dreams [XR].odin\"" >> "$cmakefile"
echo "    \"Soundbanks/Factory Presets/Atmospheres/Frosty Atmo [tx].odin\"" >> "$cmakefile"
echo "    \"Soundbanks/Factory Presets/Atmospheres/Galata Dream.odin\"" >> "$cmakefile"
echo "    \"Soundbanks/Factory Presets/Atmospheres/Messy Seq X-Y.odin\"" >> "$cmakefile"
echo "    \"Soundbanks/Factory Presets/Atmospheres/Orbitalesque Stabs [4T].odin\"" >> "$cmakefile"
echo "    \"Soundbanks/Factory Presets/Atmospheres/Pacific Nights.odin\"" >> "$cmakefile"
echo "    \"Soundbanks/Factory Presets/Atmospheres/Pulsator.odin\"" >> "$cmakefile"
echo "    \"Soundbanks/Factory Presets/Atmospheres/Sound of Paradise2 [psylion].odin\"" >> "$cmakefile"
echo "    \"Soundbanks/Factory Presets/Atmospheres/Sunrise.odin\"" >> "$cmakefile"
echo "    \"Soundbanks/Factory Presets/Atmospheres/Vector Soundtrack [XR].odin\"" >> "$cmakefile"
echo "    \"Soundbanks/Factory Presets/Atmospheres/Violet.odin\"" >> "$cmakefile"
echo "    \"Soundbanks/Factory Presets/Atmospheres/Voyage 1a X-Y.odin\"" >> "$cmakefile"
echo "    \"Soundbanks/Factory Presets/Atmospheres/Zambezi River [psylion].odin\"" >> "$cmakefile"
echo "    \"Soundbanks/Factory Presets/Bass/Analog Bass [tx].odin\"" >> "$cmakefile"
echo "    \"Soundbanks/Factory Presets/Bass/BS Decay Bass MW.odin\"" >> "$cmakefile"
echo "    \"Soundbanks/Factory Presets/Bass/BS PWM Bass XY.odin\"" >> "$cmakefile"
echo "    \"Soundbanks/Factory Presets/Bass/Bass Crusher [RM].odin\"" >> "$cmakefile"
echo "    \"Soundbanks/Factory Presets/Bass/Bass Low [RM].odin\"" >> "$cmakefile"
echo "    \"Soundbanks/Factory Presets/Bass/Bass Seq 2 [RS].odin\"" >> "$cmakefile"
echo "    \"Soundbanks/Factory Presets/Bass/Bass Simple PM [RS].odin\"" >> "$cmakefile"
echo "    \"Soundbanks/Factory Presets/Bass/Bass Wobble [4T].odin\"" >> "$cmakefile"
echo "    \"Soundbanks/Factory Presets/Bass/Bass X-Y Mod [RS].odin\"" >> "$cmakefile"
echo "    \"Soundbanks/Factory Presets/Bass/Boards Bass.odin\"" >> "$cmakefile"
echo "    \"Soundbanks/Factory Presets/Bass/DeepBass [Photonic].odin\"" >> "$cmakefile"
echo "    \"Soundbanks/Factory Presets/Bass/Growly FM Bass [XR].odin\"" >> "$cmakefile"
echo "    \"Soundbanks/Factory Presets/Bass/PM Bass [XR].odin\"" >> "$cmakefile"
echo "    \"Soundbanks/Factory Presets/Bass/Rhythm Bass.odin\"" >> "$cmakefile"
echo "    \"Soundbanks/Factory Presets/Bass/Sausage Bassener.odin\"" >> "$cmakefile"
echo "    \"Soundbanks/Factory Presets/Chimes/Arp-Bells [Photonic].odin\"" >> "$cmakefile"
echo "    \"Soundbanks/Factory Presets/Chimes/Cheese Pad.odin\"" >> "$cmakefile"
echo "    \"Soundbanks/Factory Presets/Chimes/Chimes [Photonic].odin\"" >> "$cmakefile"
echo "    \"Soundbanks/Factory Presets/Chimes/Ethereal Bells.odin\"" >> "$cmakefile"
echo "    \"Soundbanks/Factory Presets/Chimes/FM Church Bells [RS].odin\"" >> "$cmakefile"
echo "    \"Soundbanks/Factory Presets/Chimes/Glass Harp A slow.odin\"" >> "$cmakefile"
echo "    \"Soundbanks/Factory Presets/Chimes/Glass Morph XY [RS].odin\"" >> "$cmakefile"
echo "    \"Soundbanks/Factory Presets/Chimes/New Age Lead.odin\"" >> "$cmakefile"
echo "    \"Soundbanks/Factory Presets/Chimes/PRC GlassHit.odin\"" >> "$cmakefile"
echo "    \"Soundbanks/Factory Presets/Chimes/Pad Sine.odin\"" >> "$cmakefile"
echo "    \"Soundbanks/Factory Presets/Chimes/Synth Glass .odin\"" >> "$cmakefile"
echo "    \"Soundbanks/Factory Presets/Chimes/Synth Glassybell.odin\"" >> "$cmakefile"
echo "    \"Soundbanks/Factory Presets/Chimes/Vibraphone.odin\"" >> "$cmakefile"
echo "    \"Soundbanks/Factory Presets/Chiptune/Bagpipe Tune.odin\"" >> "$cmakefile"
echo "    \"Soundbanks/Factory Presets/Chiptune/Chippy.odin\"" >> "$cmakefile"
echo "    \"Soundbanks/Factory Presets/Chiptune/ChippyDelayed.odin\"" >> "$cmakefile"
echo "    \"Soundbanks/Factory Presets/Chiptune/Chiptune Chords [Projektor].odin\"" >> "$cmakefile"
echo "    \"Soundbanks/Factory Presets/Chiptune/Lead 64.odin\"" >> "$cmakefile"
echo "    \"Soundbanks/Factory Presets/Chiptune/Legal Looting [yellowmix].odin\"" >> "$cmakefile"
echo "    \"Soundbanks/Factory Presets/Chiptune/PM Sequence.odin\"" >> "$cmakefile"
echo "    \"Soundbanks/Factory Presets/Chiptune/Pad Arpeggio.odin\"" >> "$cmakefile"
echo "    \"Soundbanks/Factory Presets/Chiptune/Rect In Peace.odin\"" >> "$cmakefile"
echo "    \"Soundbanks/Factory Presets/Chiptune/Rhythmic Sequence 01.odin\"" >> "$cmakefile"
echo "    \"Soundbanks/Factory Presets/Chiptune/Shortchip.odin\"" >> "$cmakefile"
echo "    \"Soundbanks/Factory Presets/Drones/Alone in the Subway.odin\"" >> "$cmakefile"
echo "    \"Soundbanks/Factory Presets/Drones/Circus Horror Show.odin\"" >> "$cmakefile"
echo "    \"Soundbanks/Factory Presets/Drones/Creep ATMO [psylion].odin\"" >> "$cmakefile"
echo "    \"Soundbanks/Factory Presets/Drones/Dark-Psy FX [psylion].odin\"" >> "$cmakefile"
echo "    \"Soundbanks/Factory Presets/Drones/Fresh Breeze.odin\"" >> "$cmakefile"
echo "    \"Soundbanks/Factory Presets/Drones/High Tea [4T].odin\"" >> "$cmakefile"
echo "    \"Soundbanks/Factory Presets/Drones/Lead Sinematic.odin\"" >> "$cmakefile"
echo "    \"Soundbanks/Factory Presets/Drones/MAD PAD 3.odin\"" >> "$cmakefile"
echo "    \"Soundbanks/Factory Presets/Drones/Prophet.odin\"" >> "$cmakefile"
echo "    \"Soundbanks/Factory Presets/Drones/S&H harsh .odin\"" >> "$cmakefile"
echo "    \"Soundbanks/Factory Presets/Drones/Swell Bits.odin\"" >> "$cmakefile"
echo "    \"Soundbanks/Factory Presets/Drones/Synth Unleash [RM].odin\"" >> "$cmakefile"
echo "    \"Soundbanks/Factory Presets/Drones/The Sound of Agony [psylion].odin\"" >> "$cmakefile"
echo "    \"Soundbanks/Factory Presets/Drones/Timmy got some meth [psylion].odin\"" >> "$cmakefile"
echo "    \"Soundbanks/Factory Presets/Drums/Clap [RS].odin\"" >> "$cmakefile"
echo "    \"Soundbanks/Factory Presets/Drums/Claps [Photonic].odin\"" >> "$cmakefile"
echo "    \"Soundbanks/Factory Presets/Drums/Crash-1 [Photonic].odin\"" >> "$cmakefile"
echo "    \"Soundbanks/Factory Presets/Drums/Drum Machine.odin\"" >> "$cmakefile"
echo "    \"Soundbanks/Factory Presets/Drums/Flange Hat.odin\"" >> "$cmakefile"
echo "    \"Soundbanks/Factory Presets/Drums/Hi-Hat 8th Seq [RS].odin\"" >> "$cmakefile"
echo "    \"Soundbanks/Factory Presets/Drums/Hi-Hat [RS].odin\"" >> "$cmakefile"
echo "    \"Soundbanks/Factory Presets/Drums/HiHat-closed [Photonic].odin\"" >> "$cmakefile"
echo "    \"Soundbanks/Factory Presets/Drums/Kick 1 XY [RS].odin\"" >> "$cmakefile"
echo "    \"Soundbanks/Factory Presets/Drums/Kick tekmid.odin\"" >> "$cmakefile"
echo "    \"Soundbanks/Factory Presets/Drums/Kick-1 [Photonic].odin\"" >> "$cmakefile"
echo "    \"Soundbanks/Factory Presets/Drums/Marching [Photonic].odin\"" >> "$cmakefile"
echo "    \"Soundbanks/Factory Presets/Drums/Shaker [Photonic].odin\"" >> "$cmakefile"
echo "    \"Soundbanks/Factory Presets/Drums/Shakers [RS].odin\"" >> "$cmakefile"
echo "    \"Soundbanks/Factory Presets/Drums/Simple Hat [Projektor].odin\"" >> "$cmakefile"
echo "    \"Soundbanks/Factory Presets/Drums/Snappy Snare [Projektor].odin\"" >> "$cmakefile"
echo "    \"Soundbanks/Factory Presets/Drums/SnarNoize.odin\"" >> "$cmakefile"
echo "    \"Soundbanks/Factory Presets/Drums/Snare 1 [RS].odin\"" >> "$cmakefile"
echo "    \"Soundbanks/Factory Presets/Drums/Snare-1 [Photonic].odin\"" >> "$cmakefile"
echo "    \"Soundbanks/Factory Presets/Drums/Snare-2 [Photonic].odin\"" >> "$cmakefile"
echo "    \"Soundbanks/Factory Presets/Drums/Taiko-Drums [Photonic].odin\"" >> "$cmakefile"
echo "    \"Soundbanks/Factory Presets/Drums/Toms 1 [RS].odin\"" >> "$cmakefile"
echo "    \"Soundbanks/Factory Presets/Drums/Toms 2 [RS].odin\"" >> "$cmakefile"
echo "    \"Soundbanks/Factory Presets/Drums/Toms-1 [Photonic].odin\"" >> "$cmakefile"
echo "    \"Soundbanks/Factory Presets/Drums/War-Drum [Photonic].odin\"" >> "$cmakefile"
echo "    \"Soundbanks/Factory Presets/Drums/kick 909.odin\"" >> "$cmakefile"
echo "    \"Soundbanks/Factory Presets/Instruments/Accordion.odin\"" >> "$cmakefile"
echo "    \"Soundbanks/Factory Presets/Instruments/Brass Pad.odin\"" >> "$cmakefile"
echo "    \"Soundbanks/Factory Presets/Instruments/Celeste.odin\"" >> "$cmakefile"
echo "    \"Soundbanks/Factory Presets/Instruments/Chello (MW,AT) [Photonic].odin\"" >> "$cmakefile"
echo "    \"Soundbanks/Factory Presets/Instruments/Chinese Steel [4T-RS].odin\"" >> "$cmakefile"
echo "    \"Soundbanks/Factory Presets/Instruments/DistGuit (MW,AT) [Photonic].odin\"" >> "$cmakefile"
echo "    \"Soundbanks/Factory Presets/Instruments/DoubleBass(MW) [Photonic].odin\"" >> "$cmakefile"
echo "    \"Soundbanks/Factory Presets/Instruments/FM Steel Drum [RS].odin\"" >> "$cmakefile"
echo "    \"Soundbanks/Factory Presets/Instruments/Flute (MW,AT) [Photonic].odin\"" >> "$cmakefile"
echo "    \"Soundbanks/Factory Presets/Instruments/Jazzguitar (MW) [Photonic].odin\"" >> "$cmakefile"
echo "    \"Soundbanks/Factory Presets/Instruments/MusicBox [Photonic].odin\"" >> "$cmakefile"
echo "    \"Soundbanks/Factory Presets/Instruments/OB Brass.odin\"" >> "$cmakefile"
echo "    \"Soundbanks/Factory Presets/Instruments/Sitar Echo.odin\"" >> "$cmakefile"
echo "    \"Soundbanks/Factory Presets/Instruments/Steel Drums.odin\"" >> "$cmakefile"
echo "    \"Soundbanks/Factory Presets/Instruments/Steeldrum [Photonic].odin\"" >> "$cmakefile"
echo "    \"Soundbanks/Factory Presets/Instruments/Tuba.odin\"" >> "$cmakefile"
echo "    \"Soundbanks/Factory Presets/Keys/E-Piano (MW) [Photonic].odin\"" >> "$cmakefile"
echo "    \"Soundbanks/Factory Presets/Keys/Electric Piano [tx].odin\"" >> "$cmakefile"
echo "    \"Soundbanks/Factory Presets/Keys/FM Piano.odin\"" >> "$cmakefile"
echo "    \"Soundbanks/Factory Presets/Keys/FX Piano.odin\"" >> "$cmakefile"
echo "    \"Soundbanks/Factory Presets/Keys/Funky-D6 [Photonic].odin\"" >> "$cmakefile"
echo "    \"Soundbanks/Factory Presets/Keys/Funky-D6.odin\"" >> "$cmakefile"
echo "    \"Soundbanks/Factory Presets/Keys/Mellow Keys [tx].odin\"" >> "$cmakefile"
echo "    \"Soundbanks/Factory Presets/Keys/Metallic Keys [XR].odin\"" >> "$cmakefile"
echo "    \"Soundbanks/Factory Presets/Keys/PhasClavi (AT) [Photonic].odin\"" >> "$cmakefile"
echo "    \"Soundbanks/Factory Presets/Keys/Phuzz Piano.odin\"" >> "$cmakefile"
echo "    \"Soundbanks/Factory Presets/Keys/Pianet.odin\"" >> "$cmakefile"
echo "    \"Soundbanks/Factory Presets/Keys/Piano Ballad 3.odin\"" >> "$cmakefile"
echo "    \"Soundbanks/Factory Presets/Keys/Piano [Photonic].odin\"" >> "$cmakefile"
echo "    \"Soundbanks/Factory Presets/Keys/SynKeys 2 [RS].odin\"" >> "$cmakefile"
echo "    \"Soundbanks/Factory Presets/Keys/SynKeys 3XY [RS].odin\"" >> "$cmakefile"
echo "    \"Soundbanks/Factory Presets/Keys/Synth Piano.odin\"" >> "$cmakefile"
echo "    \"Soundbanks/Factory Presets/Keys/Toy Piano.odin\"" >> "$cmakefile"
echo "    \"Soundbanks/Factory Presets/Leads/Cuaroth [yellowmix].odin\"" >> "$cmakefile"
echo "    \"Soundbanks/Factory Presets/Leads/Drawing Lead.odin\"" >> "$cmakefile"
echo "    \"Soundbanks/Factory Presets/Leads/EDM Synth Projektor.odin\"" >> "$cmakefile"
echo "    \"Soundbanks/Factory Presets/Leads/Filter LFO Lead.odin\"" >> "$cmakefile"
echo "    \"Soundbanks/Factory Presets/Leads/Glide Comb Lead.odin\"" >> "$cmakefile"
echo "    \"Soundbanks/Factory Presets/Leads/Karplus Lead.odin\"" >> "$cmakefile"
echo "    \"Soundbanks/Factory Presets/Leads/Lead Glide.odin\"" >> "$cmakefile"
echo "    \"Soundbanks/Factory Presets/Leads/Lead Rusty.odin\"" >> "$cmakefile"
echo "    \"Soundbanks/Factory Presets/Leads/Lead Sine.odin\"" >> "$cmakefile"
echo "    \"Soundbanks/Factory Presets/Leads/Lead Square A.odin\"" >> "$cmakefile"
echo "    \"Soundbanks/Factory Presets/Leads/Lead Squarepusher.odin\"" >> "$cmakefile"
echo "    \"Soundbanks/Factory Presets/Leads/LeadPuls (AT,MW) [Photonic].odin\"" >> "$cmakefile"
echo "    \"Soundbanks/Factory Presets/Leads/Meeting Of Three.odin\"" >> "$cmakefile"
echo "    \"Soundbanks/Factory Presets/Leads/Pad cheapo.odin\"" >> "$cmakefile"
echo "    \"Soundbanks/Factory Presets/Leads/Random Voices.odin\"" >> "$cmakefile"
echo "    \"Soundbanks/Factory Presets/Leads/Reverse Lead.odin\"" >> "$cmakefile"
echo "    \"Soundbanks/Factory Presets/Leads/Rnd Delay Lead.odin\"" >> "$cmakefile"
echo "    \"Soundbanks/Factory Presets/Leads/Synth Brass.odin\"" >> "$cmakefile"
echo "    \"Soundbanks/Factory Presets/Leads/Unison Glide Lead.odin\"" >> "$cmakefile"
echo "    \"Soundbanks/Factory Presets/Leads/Vibrato Lead.odin\"" >> "$cmakefile"
echo "    \"Soundbanks/Factory Presets/Organ/666-001-Organ.odin\"" >> "$cmakefile"
echo "    \"Soundbanks/Factory Presets/Organ/Church Organ.odin\"" >> "$cmakefile"
echo "    \"Soundbanks/Factory Presets/Organ/Glass Organ.odin\"" >> "$cmakefile"
echo "    \"Soundbanks/Factory Presets/Organ/Organ 0001.odin\"" >> "$cmakefile"
echo "    \"Soundbanks/Factory Presets/Organ/Organ Tremolo.odin\"" >> "$cmakefile"
echo "    \"Soundbanks/Factory Presets/Organ/Pad Pleasure.odin\"" >> "$cmakefile"
echo "    \"Soundbanks/Factory Presets/Organ/Phazzy Organ.odin\"" >> "$cmakefile"
echo "    \"Soundbanks/Factory Presets/Organ/Pipe Dreams [yellowmix].odin\"" >> "$cmakefile"
echo "    \"Soundbanks/Factory Presets/Organ/Sparkle Organ.odin\"" >> "$cmakefile"
echo "    \"Soundbanks/Factory Presets/Organ/Suitcase n Amp [yellowmix].odin\"" >> "$cmakefile"
echo "    \"Soundbanks/Factory Presets/Pads/Boards 2.odin\"" >> "$cmakefile"
echo "    \"Soundbanks/Factory Presets/Pads/Burble Pad.odin\"" >> "$cmakefile"
echo "    \"Soundbanks/Factory Presets/Pads/Choir Aahs 1 [RS].odin\"" >> "$cmakefile"
echo "    \"Soundbanks/Factory Presets/Pads/Choir Aahs 2 [RS].odin\"" >> "$cmakefile"
echo "    \"Soundbanks/Factory Presets/Pads/Choir Yeah [RS].odin\"" >> "$cmakefile"
echo "    \"Soundbanks/Factory Presets/Pads/Choir [Photonic].odin\"" >> "$cmakefile"
echo "    \"Soundbanks/Factory Presets/Pads/Clouded [RM].odin\"" >> "$cmakefile"
echo "    \"Soundbanks/Factory Presets/Pads/Darken Nature [RM].odin\"" >> "$cmakefile"
echo "    \"Soundbanks/Factory Presets/Pads/Drifter.odin\"" >> "$cmakefile"
echo "    \"Soundbanks/Factory Presets/Pads/FM Sphere [RS].odin\"" >> "$cmakefile"
echo "    \"Soundbanks/Factory Presets/Pads/Female aah mellow.odin\"" >> "$cmakefile"
echo "    \"Soundbanks/Factory Presets/Pads/Female aah.odin\"" >> "$cmakefile"
echo "    \"Soundbanks/Factory Presets/Pads/Haunt [RM].odin\"" >> "$cmakefile"
echo "    \"Soundbanks/Factory Presets/Pads/Moonshade.odin\"" >> "$cmakefile"
echo "    \"Soundbanks/Factory Presets/Pads/PAD Open.odin\"" >> "$cmakefile"
echo "    \"Soundbanks/Factory Presets/Pads/Portapotty.odin\"" >> "$cmakefile"
echo "    \"Soundbanks/Factory Presets/Pads/Strings (MW,AT) [Photonic].odin\"" >> "$cmakefile"
echo "    \"Soundbanks/Factory Presets/Pads/Strings short (MW) [Photonic].odin\"" >> "$cmakefile"
echo "    \"Soundbanks/Factory Presets/Pads/Sweeper 3.odin\"" >> "$cmakefile"
echo "    \"Soundbanks/Factory Presets/Pads/Synae XY [RS].odin\"" >> "$cmakefile"
echo "    \"Soundbanks/Factory Presets/Pads/Synth Ballad.odin\"" >> "$cmakefile"
echo "    \"Soundbanks/Factory Presets/Pads/Synth Strings.odin\"" >> "$cmakefile"
echo "    \"Soundbanks/Factory Presets/Pads/Synth Strings2.odin\"" >> "$cmakefile"
echo "    \"Soundbanks/Factory Presets/Pads/Synthwave Pad.odin\"" >> "$cmakefile"
echo "    \"Soundbanks/Factory Presets/Pads/VangBrass (MW,AT) [Photonic].odin\"" >> "$cmakefile"
echo "    \"Soundbanks/Factory Presets/Pads/Voices.odin\"" >> "$cmakefile"
echo "    \"Soundbanks/Factory Presets/Pads/Warm-Pad [Photonic].odin\"" >> "$cmakefile"
echo "    \"Soundbanks/Factory Presets/Pads/forever young.odin\"" >> "$cmakefile"
echo "    \"Soundbanks/Factory Presets/Pads/sounds like a melody.odin\"" >> "$cmakefile"
echo "    \"Soundbanks/Factory Presets/SFX/Alien Arp.odin\"" >> "$cmakefile"
echo "    \"Soundbanks/Factory Presets/SFX/Cheering Minions.odin\"" >> "$cmakefile"
echo "    \"Soundbanks/Factory Presets/SFX/Doctor Acid.odin\"" >> "$cmakefile"
echo "    \"Soundbanks/Factory Presets/SFX/Drippin Droplets.odin\"" >> "$cmakefile"
echo "    \"Soundbanks/Factory Presets/SFX/Drone S&H.odin\"" >> "$cmakefile"
echo "    \"Soundbanks/Factory Presets/SFX/Dropper [RS].odin\"" >> "$cmakefile"
echo "    \"Soundbanks/Factory Presets/SFX/FM-XY Fun [RS].odin\"" >> "$cmakefile"
echo "    \"Soundbanks/Factory Presets/SFX/FX Jump [RM].odin\"" >> "$cmakefile"
echo "    \"Soundbanks/Factory Presets/SFX/FX Pitch Down [RM].odin\"" >> "$cmakefile"
echo "    \"Soundbanks/Factory Presets/SFX/FX Reso Warble.odin\"" >> "$cmakefile"
echo "    \"Soundbanks/Factory Presets/SFX/Flange Fun [psylion].odin\"" >> "$cmakefile"
echo "    \"Soundbanks/Factory Presets/SFX/Formant Squelch.odin\"" >> "$cmakefile"
echo "    \"Soundbanks/Factory Presets/SFX/German Glitches.odin\"" >> "$cmakefile"
echo "    \"Soundbanks/Factory Presets/SFX/PSY Noise Squelch .odin\"" >> "$cmakefile"
echo "    \"Soundbanks/Factory Presets/SFX/Pipe FX.odin\"" >> "$cmakefile"
echo "    \"Soundbanks/Factory Presets/SFX/Plastic Riser 1 [RS].odin\"" >> "$cmakefile"
echo "    \"Soundbanks/Factory Presets/SFX/Plastic Riser 2 [RS].odin\"" >> "$cmakefile"
echo "    \"Soundbanks/Factory Presets/SFX/S&H noise.odin\"" >> "$cmakefile"
echo "    \"Soundbanks/Factory Presets/SFX/Something Awakens.odin\"" >> "$cmakefile"
echo "    \"Soundbanks/Factory Presets/SFX/Space Shuttle [psylion].odin\"" >> "$cmakefile"
echo "    \"Soundbanks/Factory Presets/SFX/Voices in my head [psylion].odin\"" >> "$cmakefile"
echo "    \"Soundbanks/Factory Presets/Stabs/Chinese Ow [4T-RS].odin\"" >> "$cmakefile"
echo "    \"Soundbanks/Factory Presets/Stabs/Chord Pluck Projektor.odin\"" >> "$cmakefile"
echo "    \"Soundbanks/Factory Presets/Stabs/Deep Triads (velo).odin\"" >> "$cmakefile"
echo "    \"Soundbanks/Factory Presets/Stabs/Dub Synth.odin\"" >> "$cmakefile"
echo "    \"Soundbanks/Factory Presets/Stabs/Gurgles dirty.odin\"" >> "$cmakefile"
echo "    \"Soundbanks/Factory Presets/Stabs/Gurgles.odin\"" >> "$cmakefile"
echo "    \"Soundbanks/Factory Presets/Stabs/House Stab.odin\"" >> "$cmakefile"
echo "    \"Soundbanks/Factory Presets/Stabs/JMJ-Sync [Photonic].odin\"" >> "$cmakefile"
echo "    \"Soundbanks/Factory Presets/Stabs/LFO Keys.odin\"" >> "$cmakefile"
echo "    \"Soundbanks/Factory Presets/Stabs/Lead 17.odin\"" >> "$cmakefile"
echo "    \"Soundbanks/Factory Presets/Stabs/Lead Hit 1.odin\"" >> "$cmakefile"
echo "    \"Soundbanks/Factory Presets/Stabs/Lead phazz.odin\"" >> "$cmakefile"
echo "    \"Soundbanks/Factory Presets/Stabs/Metallic (vel).odin\"" >> "$cmakefile"
echo "    \"Soundbanks/Factory Presets/Stabs/Pad House.odin\"" >> "$cmakefile"
echo "    \"Soundbanks/Factory Presets/Stabs/Pluck.odin\"" >> "$cmakefile"
echo "    \"Soundbanks/Factory Presets/Stabs/Plucker 3.odin\"" >> "$cmakefile"
echo "    \"Soundbanks/Factory Presets/Stabs/Saw Pluck [Projektor].odin\"" >> "$cmakefile"
echo "    \"init_patch.odin\"" >> "$cmakefile"
echo "    \"font/aldrich_regular.ttf\"" >> "$cmakefile"
echo "    \"spline_ad.png\"" >> "$cmakefile"
echo "" >> "$cmakefile"


progress=0
# loop over images in directory
for filename in $(find . -name '*.png'); do
        
    echo "[$progress / $numfiles] $filename"

    baseFilePath=${filename%.png}
    baseFileName="$(basename -- $baseFilePath)"
    #echo "$baseFileName"

    echo "    ${baseFileName}," >> "$indexfile"
    echo "    BinaryData::${baseFileName}_png," >> "$datafile"
    echo "    BinaryData::${baseFileName}_pngSize," >> "$sizefile"
    echo "    \"${filename}\"" >> "$cmakefile"

    progress=$((progress+1))
done

echo "    NumIndices" >> "$indexfile"
echo "};" >> "$indexfile"
echo "}" >> "$indexfile"

echo "};" >> "$datafile"

echo "};" >> "$sizefile"

echo ")" >> "$cmakefile"
