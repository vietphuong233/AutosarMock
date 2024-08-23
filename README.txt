Thành viên nhóm 1B:
  CuongNK26
  PhuongNV40

Nội dung (áp dụng cho mọi ECU):
  app: source code .c định nghĩa các runnables
  common: các file .h chứa các định nghĩa chung được dùng cho project
  rte:
    - Rte_<swc_name>.c: định nghĩa các hàm RTE được dùng trong các runnable
    - OsTask_<task_name>.c: định nghĩa task 
    - Rte.h: chứa các định nghĩa cố định cho các ECU
    - Rte_<swc_name>.h: header riêng cho các SWC, chứa các nguyên mẫu hàm API RTE và nguyên mẫu hàm các Runnable 
    - Rte_Type: chứa các khai báo của các kiểu dữ liệu được dùng trong RTE, ví dụ: AUTOSAR_uint8, NvM_BlockIdType,...
    - Rte_DataHandle.h: chứa các khai báo kiểu dữ liệu được dùng trong SWC
    - Rte_<swc_name>_Type.h: chứa các khai báo hằng số được dùng trong SWC
    - Rte_Cbk.c & Rte_Cbk.h: khai báo và định nghĩa các hàm COM Call Back