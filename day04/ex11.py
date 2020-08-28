#%%
_a = 'hello helo heo helo ello helo hleo'
_b = 'libex04'
_c = 'libex03'
_a.startswith('he')

#%% 끝이 ~로 끝나는지
_a.endswith('lo')

#%% 시작을 ~로 하는지
_b.startswith('lib')

#%% 몇번째에 있는지
_c.find('ex')

#%% 카운트
_a.count('llo')

#%%
_lt = "          front line          "
print('before' + _lt)
__lt = str.lstrip(_lt)
print('after' + _lt)
print('after' + __lt)

#%%
_lt = "          front line          "
__lt = _lt.lstrip()
print('after' + _lt)
print('after' + __lt)

#%%
print(str.isalpha('helllo'))

#%%
print(str.isdigit('helllo'))
print(str.isdigit('314'))

#%%
name = 'PGJ'
age = 27
print(f'my name : {name}, my age : {age}')

# %%
data = "Park Gwang-Jin"
_data = data.split()
print(_data[0])
print(_data[1])

#%%
data = "kor/eng/math/the society"

data.split('/')

#%%
data = input()
data.split()


# %%
