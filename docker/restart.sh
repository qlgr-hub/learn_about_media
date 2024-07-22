#!/usr/bin/env bash

set -e

docker compose stop
docker compose -p av_dev -f ./docker-compose.yml up -d  --build --force-recreate
