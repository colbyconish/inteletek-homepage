FROM archlinux:latest 

# Update and install necessary packages
RUN pacman -Syu --noconfirm make cmake git gcc openssl yaml-cpp 

# Build web app
WORKDIR /app
COPY . . 
RUN cmake -S. -Bbuild
RUN cmake --build build --parallel 10

# Move config and assets into correct location
RUN mv webserver.json /etc/
RUN mv www /www

# Start web server
CMD build/homepage

# Expose port 80
EXPOSE 80/tcp
