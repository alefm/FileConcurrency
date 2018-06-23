FROM gcc:4.9
WORKDIR /app
COPY . /app
CMD ./file_concurrency TRUE