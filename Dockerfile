FROM archlinux:latest 

# Update and install necessary packages
RUN pacman -Syu --noconfirm yaml-cpp make cmake git gcc

# Build drogon
RUN git clone --recursive https://github.com/drogonframework/drogon.git drogon 
RUN cmake -S drogon -B drogon/build
RUN cmake --build drogon/build --parallel 10
RUN cd drogon/build && make install 

# Build C-ares
RUN git clone https://github.com/c-ares/c-ares.git c-ares
RUN cmake -S c-ares -B c-ares/build
RUN cmake --build c-ares/build --parallel 10
RUN cd c-ares/build && make install

# Build web app
WORKDIR /app
COPY . . 
RUN make --jobs 10

# Move config and assets into correct location
RUN mv webserver.json /etc/
RUN mv www /www

# Start web server
CMD LD_LIBRARY_PATH="$LD_LIBRARY_PATH:/usr/local/lib" build/web_server

# Expose port 80
EXPOSE 80/tcp
