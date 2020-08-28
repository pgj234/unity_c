#%%
a=5
b=1
def scope_test() :
    global a
    a=1
    b=7
    print(a, b)

scope_test()
print(a, b)
# %%
count = 0
def recur_test() :
    global count
    if count < 5:
        count = count +1
        print(count)
        recur_test()

recur_test()

# %%
def hello() :
    print('hello')
a = hello
a()
# %%
# def count() :
#     count =0
#     def closer() :
#         count = count +1
#         print(count)
#     return closer

# _count = count
# _count()
# _count()