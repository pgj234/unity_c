#%%

limit = 5
count = 0

while count < limit :
    print('repeat!!')
    count = count +1

print("------------------------------")
# %%

for i in [1, 2, 3] :
    print(i)
# %%
for i in range(10) :
    print(i)
for i in range(95, 100) :
    print(i)
print("-----------------------------")
for i in range(0, 5, 2) :
    print(i)

# %%

for i in range(5) :
    for j in range(i +1) :
        print("*", end="")
    print("")

# %%
limit = 5
count = 0
while True :
    if count > limit :
        break
    print(f'loop!! {count}')
    count = count +1

print('exit loop')
# %%

for i in range(10) :
    if i%2 :
        continue
    print(i)
print('_______________')
# %%
