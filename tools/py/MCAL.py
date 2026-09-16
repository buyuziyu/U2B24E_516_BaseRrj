import os
import shutil
from pathlib import Path

符号_文件路径分隔符 = '\\'

Path_MCAL目录   = '\\code\\R_MCAL'
Path_公共文件   = '\\code\\R_MCAL\\common'
Path_第三方     = '\\code\\R_MCAL\\stubs'
Path_Sample代码 = '\\code\\R_MCAL\\SampleCode'
Path_模块代码   = '\\code\\R_MCAL\\modules'
Path_静态代码   = '\\code\\R_MCAL\\modules\\StaticCode'
Path_配置代码   = '\\code\\R_MCAL\\modules\\ConfigCode'

文件路径_MCAL根目录 = ''
文件路径_工程根目录 = ''

Array_file_rel_path = []
FileNum = 0

# 记录所有 .c .h 文件放入数组 Array_file_rel_path = [[文件名, 相对路径]]
def 接口_遍历所有文件类型(base_dir):

    global Array_file_rel_path
    global FileNum

    base_dir = os.path.abspath(base_dir)  # 转换为绝对路径确保一致性
    Array_file_rel_path = []
    
    for root, _, files in os.walk(base_dir):
        for file in files:
            if file.endswith(('.c', '.h')):
                # 获取文件所在目录的相对路径（相对于base_dir）
                rel_dir = os.path.relpath(root, base_dir)
                # 避免根目录显示为"."，改为空字符串
                rel_dir = rel_dir if rel_dir != '.' else ''
                Array_file_rel_path.append([file, rel_dir])
                FileNum += 1
    

def 接口_移植文件(文件名,文件相对路径):

    global Path_MCAL目录
    global Path_公共文件
    global Path_第三方
    global Path_Sample代码
    global Path_静态代码
    global Path_配置代码

    global 文件路径_MCAL根目录
    global 文件路径_工程根目录


    Temp_未处理文件 = 0

    # 拆分路径
    dir_lists = 文件相对路径.split(符号_文件路径分隔符)
    Temp_源文件     = 文件路径_MCAL根目录 + '\\' + 文件相对路径 + '\\' + 文件名


    if 'sample_application' in dir_lists:
        dir_lists[1], dir_lists[3] = dir_lists[3], dir_lists[1]
        dir_lists.remove('modules')

    # stubs 类型文件
    if 'stubs' in dir_lists:
        Temp_目标路径   = 文件路径_工程根目录 + Path_第三方
        dir_lists.remove('common')

    # sample_application 类型文件
    elif 'sample_application' in dir_lists:
        Temp_目标路径   = 文件路径_工程根目录 + Path_Sample代码

    # 静态代码 类型文件
    elif 'modules' in dir_lists:
        Temp_目标路径   = 文件路径_工程根目录 + Path_静态代码

    # common 类型文件
    elif 'common' in dir_lists:
        Temp_目标路径   = 文件路径_工程根目录 + Path_公共文件
        if 'modules' not in dir_lists:
            delete_list = ['common']
            new_dir_lists = [x for x in dir_lists if x not in delete_list]
            dir_lists = new_dir_lists

    # 配置代码 类型文件
    elif 'MCAL_RH850U2Ax_CodeGen' in dir_lists or 'MCAL_RH850U2Bx_CodeGen' in dir_lists or 'MCAL_RH850U2Cx_CodeGen' in dir_lists:
        Temp_目标路径   = 文件路径_工程根目录 + Path_配置代码

    # scripts 类型文件
    elif 'scripts' in dir_lists:
        print('  MCAL包中未移植文件\t' + 文件相对路径 + '\t' + 文件名)
        Temp_未处理文件 = 1

    # 未处理文件
    else:
        print('  MCAL包中未移植文件\t' + 文件相对路径 + '\t' + 文件名)
        Temp_未处理文件 = 1

    if Temp_未处理文件 == 0:

        delete_list = ['X2x', 'ghs', 'generic', '22_11', '4_3_1', 'compiler', 'MCAL_RH850U2Ax_CodeGen', 'MCAL_RH850U2Bx_CodeGen', 'MCAL_RH850U2Cx_CodeGen', 'modules', 'sample_application', 'stubs']
        new_dir_lists = [x for x in dir_lists if x not in delete_list]
        if '_MemMap.h' in 文件名:
            new_dir_lists.remove('include')
            new_dir_lists.append('MemMap')

        for list in new_dir_lists:
            Temp_目标路径 += '\\' + list
        接口_根据传入路径生成文件夹(Temp_目标路径)
        shutil.copy2(Temp_源文件, Temp_目标路径)


def 接口_根据传入路径生成文件夹(工程MCAL绝对路径):
    """
    递归检查并创建路径中的所有目录
    :param folder_path: 输入的文件夹路径（绝对或相对路径）
    :return: None
    """
    try:
        # 转换为Path对象处理跨平台路径
        path = Path(工程MCAL绝对路径)
        
        # 检查路径有效性
        if not path.parts:
            raise ValueError("无效路径：路径为空")
            
        # 递归创建目录（parents=True创建父级，exist_ok=True忽略已存在目录）
        path.mkdir(parents=True, exist_ok=True)
        # print(f"目录已创建或已存在：{path.resolve()}")
        
    except PermissionError:
        print(f"  权限不足：无法创建目录 {path}")
    except Exception as e:
        print(f"  目录创建失败：{str(e)}")


def get_MCAL_files(MCAL根目录, 工程根目录):

    global Path_MCAL目录
    global Path_模块代码
    global Path_公共文件
    global Path_第三方

    global 文件路径_MCAL根目录
    global 文件路径_工程根目录

    文件路径_工程根目录 = 工程根目录
    文件路径_MCAL根目录 = MCAL根目录

    try:
        shutil.rmtree(文件路径_工程根目录 + Path_公共文件)
        shutil.rmtree(文件路径_工程根目录 + Path_第三方)
        shutil.rmtree(文件路径_工程根目录 + Path_Sample代码)
        shutil.rmtree(文件路径_工程根目录 + Path_模块代码)
    except Exception as e:
        print('  指定删除文件夹不存在')

    接口_遍历所有文件类型(文件路径_MCAL根目录)
    
    for 文件名, 相对路径 in Array_file_rel_path:
        接口_移植文件(文件名, 相对路径)