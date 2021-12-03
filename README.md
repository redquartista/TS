# TS

1. Clean the workspace by removing old binaries / output files. 
make clean

2. Compile the application
make

3. Run the application

./ts_demux <input_file> <output_video_file> <output_audio_file>

# Usage
The ts_demux app requires 3 arguments:
1. Input file location
2. Output video file location
3. Output audio file location

The correct usage is: ./ts_demux <input_file> <output_video_file> <output_audio_file>

e.g. ./ts_demux /tmp/watermarking_test_task.ts /tmp/video.mp4 /tmp/audio.wav
