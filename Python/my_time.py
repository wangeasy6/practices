import datetime

birthday = datetime.datetime(1996, 1, 9, 0, 0, 0)
now_time = datetime.datetime.now()
life_time = now_time - birthday
days = life_time.days
seconds = life_time.seconds

print 'life has been gone: %d years, %s days. %d hours, %d min, %d seconds' % (days/365, days%365,  seconds/3600, seconds%3600/60, seconds%3600%60)