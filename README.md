# Fragrancy-Forged-Memoryscapes
Interactive olfactory installation on memory activation

Things to change (IR_OSC files):
- char ssid[] -> Wifi name network
- char pass[] -> Wifi password
- const IPAddress outIP -> main PC IP

Things to change (touchdesigner):
- relink the audio/video files

  Nice to do: set a fix IP on the PC and make sure that arduinos are disconnected whenever the PC is turned on for the first time (to avoid arduino stealing the ip).
