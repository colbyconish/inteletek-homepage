FROM archlinux:latest as build
RUN pacman -Syu --noconfirm make cmake gcc git openssl yaml-cpp jsoncpp \
aws-sdk-cpp

COPY . . 
RUN cmake -S. -Bbuild
RUN cmake --build build --parallel 10



FROM archlinux:latest as prod
RUN pacman -Syu --noconfirm curl aws-sdk-cpp jsoncpp yaml-cpp openssl

WORKDIR /www
COPY --from=build /www/ . 
COPY --from=build /build/homepage /usr/bin
COPY --from=build /webserver.json /etc/

HEALTHCHECK CMD curl -f http://localhost:8080/health/ || exit 1

EXPOSE 8080/tcp
STOPSIGNAL SIGTERM
CMD ["homepage"]
