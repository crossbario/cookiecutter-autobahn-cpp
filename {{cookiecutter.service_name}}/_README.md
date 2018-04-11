https://github.com/crossbario/autobahn-cpp/archive/v17.5.1.zip



Building for 3 CPU architectures:

https://gist.github.com/oberstet/f663944a053d43515b2b1ff49c597a0d

On the Pi 3, with [Debian Strech Preview for Pi](https://wiki.debian.org/RaspberryPi3) which is a true 64 bit kernel and userland, running the aarch64 built executable works, but the armhf one seg faults.

https://gist.github.com/oberstet/771460a5e33f257b63335ecb18400928


Autobahn-C++ allows to create WAMP application components in C++ that can be built as a single,
statically linked executable with size below 2 MB. Once your component is built, this single
self contained file has a lot of advantages on the deployment side. However, C++ is also not
very developer friendly, and the development turnaround can run into the minutes. Compare that with
the save in editor and "it's live" workflow which is the norm in Web development.
\n\n

So we hope provides all you need to start creating Autobahn-C++ based client applications
and WAMP components in C++!





### Crossbar.io and Autobahn

To get the starter template, clone our repo

```console
cd ~
git clone https://github.com/crossbario/crossbar-starter.git
```

In a first terminal, start Crossbar.io

```console
cd ~/crossbar-starter/crossbar
make start_armhf
```

In a second terminal, start Crossbar.io

```console
cd ~/crossbar-starter/autobahn-python
make start_armhf
```

In a third terminal, start Crossbar.io

```console
cd ~/crossbar-starter/autobahn-js
make start_armhf
```

### Development Setup

One way you can do development on the Pi that we find comfortable and relatively hassle free is to mount a working directory from your development notebook on the Pi.

Determine the IP address of your notebook on the local network, assuming this is a 192er network:

```console
oberstet@thinkpad-t430s:~/scm/crossbario/crossbar-starter$ ifconfig | grep 192
          inet Adresse:192.168.55.138  Bcast:192.168.55.255  Maske:255.255.255.0
```

Further assuming your working directory is `/home/oberstet/scm`. Then to remotely mount this, login on the Pi and install **sshfs** once:

```console
sudo apt-get install sshfs
```

and then mount the remote filesystem from your notebook on the Pi:

```console
sudo sshfs -o allow_other oberstet@192.168.55.138:/home/oberstet/scm ~/scm
```

Now, you can move around in the directories on this mountpoint, and effectively you will be browsing your notebook of course.

You can also open and edit files on your notebook using your favorite editor, and the changes will be be reflected on the Pi immediately.

And this is the key for this approach to the development cycle:

- you remotely log into the Pi at the console and start components directly from a mirror of your working directory
- you open and edit files locally on your notebook using your local editor


### Bundled Images

For the Pi, the following Docker images provided by the Crossbar.io Project will work:


```console
docker pull crossbario/crossbar-armhf:community-cpy3
docker pull crossbario/autobahn-python-armhf:cpy2
docker pull crossbario/autobahn-python-armhf:cpy3
docker pull crossbario/autobahn-python-armhf:pypy2
docker pull crossbario/autobahn-python-armhf:pypy3
docker pull crossbario/autobahn-python-armhf:cpy2-minimal-aio
docker pull crossbario/autobahn-python-armhf:cpy3-minimal-aio
docker pull crossbario/autobahn-python-armhf:cpy2-minimal-tx
docker pull crossbario/autobahn-python-armhf:cpy3-minimal-tx
docker pull crossbario/autobahn-js-armhf:full
docker pull crossbario/autobahn-js-armhf:alpine
```
