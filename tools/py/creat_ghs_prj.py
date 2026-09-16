import os
import subprocess
import sys

def 接口_编译工程(GHS根目录):

    gbuild_path = os.path.join(GHS根目录, 'gbuild.exe')
    if not os.path.exists(gbuild_path):
        print(f"  GHS编译器路径异常，请检查： {gbuild_path}")
        sys.exit(1)

    if not os.path.exists(r'.\Startup.gpj'):
        print("  错误：未找到项目文件 Startup.gpj")
        sys.exit(1)

    # 运行编译
    """
    运行GHS编译命令并实时输出结果
    """
    # 设置环境变量
    os.environ['COMP_DIR'] = GHS根目录
    
    # 定义编译命令
    comp_dir = os.environ['COMP_DIR']
    gbuild_path = os.path.join(comp_dir, 'gbuild.exe')
    gpj_file = r'.\Startup.gpj'
    
    # 构建完整命令
    cmd = [gbuild_path, '-top', gpj_file]
    
    print(f"开始执行编译命令: {' '.join(cmd)}")
    print("=" * 50)
    
    try:
        # 使用Popen执行命令，实时捕获输出 [6,7](@ref)
        process = subprocess.Popen(
            cmd,
            stdout=subprocess.PIPE,
            stderr=subprocess.STDOUT,  # 将标准错误合并到标准输出
            universal_newlines=True,    # 以文本模式处理输出
            bufsize=1,                 # 行缓冲
            encoding='utf-8'           # 编码方式
        )
        
        # 实时读取输出 [6,8](@ref)
        while True:
            output = process.stdout.readline()
            if output == '' and process.poll() is not None:
                break
            if output:
                print(output.strip(), flush=True)  # 实时打印每一行
        
        # 等待进程结束并获取返回码
        return_code = process.wait()

        log_path = os.getcwd() + r"\output\build_log.txt"
        try:
            with open(log_path, 'w', encoding='utf-8') as file:
                if process.stdout:
                    file.write(str(process.stdout))
                if process.stderr:
                    file.write(str(process.stderr))
        except PermissionError:
            print(f"  错误：没有权限访问文件 {log_path}")
        except Exception as e:
            print(f"  处理文件时发生错误：{e}")

        print("=" * 50)
        if return_code == 0:
            print("  编译完成！")
        else:
            print(f"  编译失败，返回码：{return_code}")
                    
    except FileNotFoundError:
        print(f"  错误：未找到编译工具 {gbuild_path}")
    except Exception as e:
        print(f"  执行过程中发生错误：{e}")


def 接口_创建编译脚本(GHS根目录):

    file_name = [
        r'\build_',
        r'.bat'
    ]

    build_script = [
        r'@del /s /q *.o',
        r'@del /s /q *.dbo',
        r'@del /s /q *.d',
        r'@del /s /q *.mem',
        r'@del /s /q *.dla',
        r'@del /s /q *.elf',
        r'@del /s /q *.dnm',
        r'@del /s /q *.s19',
        r'@del /s /q *.hex',
        r'@del /s /q *.srec',
        r'@del /s /q *.dep',
        r'@del /s /q *.siz',
        r'@del /s /q *.map',
        r'@del /s /q build_log.txt',
        r'@set COMP_DIR=' + GHS根目录,
        r'@if not exist ".\output" mkdir ".\output"',
        r'@%COMP_DIR%\gbuild.exe -top .\Startup.gpj> ".\output\build_log.txt" 2>&1',
        r'@echo build done, see log in .\output\build_log.txt',
        r'@pause'
    ]

    file_path = os.getcwd() + file_name[0] + 'Startup' + file_name[1]
    try:
        with open(file_path, 'w', encoding='utf-8') as file:
            for content in build_script:
                file.write(content + '\n')
        print(f'  编译脚本路径: {file_path}')

    except PermissionError:
        print(f"  错误：没有权限访问文件 {file_path}")
    except Exception as e:
        print(f"  处理文件时发生错误：{e}")
