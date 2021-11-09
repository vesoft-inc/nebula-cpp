#! /usr/bin/env python3

import datetime
import argparse

parser = argparse.ArgumentParser(description='Process command line arguments.')
parser.add_argument('--day_diff', dest='day_diff', action='store', type=int)

args = parser.parse_args()

current = datetime.date.today()
day_diff = datetime.timedelta(days=args.day_diff)
current = current - day_diff

print(current.strftime('%Y.%m.%d'))
