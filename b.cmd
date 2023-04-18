@echo off
cls
cl main.c /Zi /Od /link sndfile.lib winmm.lib
