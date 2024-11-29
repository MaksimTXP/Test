FROM gcc:11.3 AS build

# Установка необходимых пакетов
RUN apt update && \
    apt install -y \
      python3-pip \
      python3-venv \
      cmake

# Создание директории приложения и виртуального окружения
WORKDIR /app
RUN python3 -m venv venv && \
    venv/bin/pip install --upgrade pip && \
    venv/bin/pip install conan==1.65.0

# Копирование и установка зависимостей через Conan
COPY conanfile.txt /app/
RUN mkdir /app/build && cd /app/build && \
    /app/venv/bin/conan install .. -s compiler.libcxx=libstdc++11 -s build_type=Debug --build=missing

# Копирование исходного кода и файлов сборки в контейнер
COPY ./src /app/src
COPY ./data /app/data
COPY ./static /app/static
COPY CMakeLists.txt /app/

# Сборка проекта
RUN cd /app/build && \
    cmake -DCMAKE_BUILD_TYPE=Release .. && \
    cmake --build .

FROM ubuntu:22.04 AS run

RUN groupadd -r www && useradd -r -g www www
USER www

COPY --from=build /app/build/bin/game_server /app/
COPY ./data /app/data
COPY ./static /app/static

ENTRYPOINT ["/app/game_server", "/app/data/config.json", "/app/static"]