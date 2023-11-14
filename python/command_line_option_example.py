import argparse

parser = argparse.ArgumentParser(description="run hive sql")

parser.add_argument("-p", "--platform", 
                    dest="platform", 
                    action='store',
                    required=True,
                    choices={'pc','mob'},
                    help="choose hive table"
                    )

parser.add_argument("--expid", 
                    dest="expid", 
                    action='store',
                    required=True,
                    help="fill in bucketid, can take multiple"
                    )

parser.add_argument("--date", 
                    dest="date", 
                    action='store',
                    required=True,
                    help="fill in date, can take multiple"
                    )

parser.platform
parser.expid
parser.date
