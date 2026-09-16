import os
from collections import defaultdict

def classify_files_by_extension():
    # 获取当前目录
    current_dir = os.getcwd()
    
    # 使用字典存储分类结果
    file_dict = defaultdict(list)
    
    # 遍历当前目录下的所有文件
    for filename in os.listdir(current_dir):
        file_path = os.path.join(current_dir, filename)
        if os.path.isfile(file_path):
            # 获取文件后缀（包含点）
            _, ext = os.path.splitext(filename)
            # 将文件添加到对应后缀的列表中
            file_dict[ext].append(filename)
    
    # 将分类结果写入txt文件
    output_file = "file_classification.txt"
    with open(output_file, "w", encoding="utf-8") as f:
        for ext, files in sorted(file_dict.items()):
            f.write(f"=== {ext if ext else '无后缀'} ===\n")
            for file in sorted(files):
                f.write(f"{file}\n")
            f.write("\n")
    
    print(f"文件分类结果已保存到 {output_file}")

if __name__ == "__main__":
    classify_files_by_extension()