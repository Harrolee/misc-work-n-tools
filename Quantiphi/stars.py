#takes a max and a min


def print_waveform(max, min):
    star = '*'
    #print max to 1 stars descending
    for i in range(max,min - 1,-1):
        print(star * i)
    #print 1-max stars ascending
    for i in range(min + 1, max + 1):
        print(star * i)
    

if __name__ == "__main__" :
    max = input("type max")
    min = input("type min")
    print_waveform(int(max), int(min))