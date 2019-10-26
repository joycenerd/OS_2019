#!/bin/bash
# check zombie process

ps -ef | grep defunct | grep -v grep | wc -l