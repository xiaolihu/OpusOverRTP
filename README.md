# OpusOverRTP
Opus as VoIP Codec. To directly decode opus over RTP packets, creating this repository.

# Build
Gradle is used to build OpusOverRTP, so you have to install and configure Gradle before you build from the git repository.

Check whether you have installed and configured Gradle correctly:

    % gradle -v

To build from the git repository, the following steps are necessary:

**0. Set up a development environment:**

    On an Ubuntu or Debian family Linux distribution:

        % sudo apt-get install git autoconf automake libtool gcc make

    On a Fedora/Redhat based Linux:

        % sudo dnf install git autoconf automake libtool gcc make

    Or for older Redhat/Centos Linux releases:

        % sudo yum install git autoconf automake libtool gcc make

    On Apple macOS, install Xcode and brew.sh, then in the Terminal enter:

        % brew install autoconf automake libtool
        
    On Windows, install Visual Studio and git for windows

##1. Clone the repository:

    % git clone https://github.com/xiaolinhu/OpusOverRTP.git
    
    % cd OpusOverRTP

##2. Build the source:

    % gradle build

Once you have build the source, there will be a VoIPCodec executable in ./build/exe/voIPCodec/debug and ./build/exe/voIPCodec/release directory.

However, besides this method, you have another method to build OpusOverRTP if on a Windows system:

1. Open ./win32/OpusOverRTP/OpusOverRTP.vcxproj with Virsual Studio;
2. Run the project.

Once you have ran the project, you can get OpusOverRTP.exe in ./win32/Debug directory.

# Usage
```
Usage  : VoIPCodec [options] <input filename> <output filename>

options:
        -d : runs the decoder
        -r <sampling rate(Hz)>: default value is 16000 Hz Supported sampling rates are 8000, 12000, 16000, 24000 and 48000
        -c <channel>: default value is 1. Supported channel are 1 and 2
```

# Reference
rtp dump format description:
http://www.cs.columbia.edu/irt/software/rtptools/

wireshar export rtp file:
https://wiki.wireshark.org/rtpdump