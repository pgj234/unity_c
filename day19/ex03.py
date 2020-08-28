#%%
#closure 를 이용한 카운터 (중요)
count = 100
def do_count() :
    count =0
    def closer() :
        nonlocal count
        count = count +1
        print(count)
    return closer

__count = do_count()
__count()
__count()

print(count)