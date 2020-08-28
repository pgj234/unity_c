#%%
print("원하시는 계산을 적으세요.")
_cmd = input()

print(f'당신은 {_cmd} 입력하셨습니다.')

#%%
_cmd = _cmd.split()

#오입력 판단
if len(_cmd) % 2 == 0 or len(_cmd) < 3 :
    print("잘못된 입력")
else :
    result = 0

    # _cmd 리스트 길이가 3이상 일 때 계속 계산
    while len(_cmd) > 2 :
        print(_cmd)

        if _cmd[1] == '+' :
            print(f'{_cmd[0]} {_cmd[1]} {_cmd[2]} = {float(_cmd[0]) + float(_cmd[2])}')
            result = float(_cmd[0]) + float(_cmd[2])
        elif _cmd[1] == '-' :
            print(f'{_cmd[0]} {_cmd[1]} {_cmd[2]} = {float(_cmd[0]) - float(_cmd[2])}')
            result = float(_cmd[0]) - float(_cmd[2])
        elif _cmd[1] == '*' :
            print(f'{_cmd[0]} {_cmd[1]} {_cmd[2]} = {float(_cmd[0]) * float(_cmd[2])}')
            result = float(_cmd[0]) * float(_cmd[2])
        elif _cmd[1] == '/' :
            print(f'{_cmd[0]} {_cmd[1]} {_cmd[2]} = {float(_cmd[0]) / float(_cmd[2])}')
            result = float(_cmd[0]) / float(_cmd[2])
        elif _cmd[1] == '%' :
            print(f'{_cmd[0]} {_cmd[1]} {_cmd[2]} = {float(_cmd[0]) % float(_cmd[2])}')
            result = float(_cmd[0]) % float(_cmd[2])
        
        print(sep = '\n')

        #결과값 인덱스 2번에 넣고 인덱스0, 1 삭제
        _cmd[2] = result
        del _cmd[0]
        del _cmd[0]

# %%
