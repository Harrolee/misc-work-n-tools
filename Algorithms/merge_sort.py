def print_list():
    unsorted = [5,3,6,8,9,3,2,5,6]
    sorted_list = merge_sort(unsorted)
    for num in sorted_list:
        print(num)



def merge_sort(unsorted):
    half_way = range(len(unsorted)//2)
    list1 = [unsorted[num] for num in range(half_way)]
    list2 = [unsorted[num] for num in range(half_way, len(unsorted))]

    



# def merge_sort(unsorted, sorted = []):
#     if len(unsorted) != 2:
#         half_way = len(unsorted)//2
#         list1 = [unsorted[num] for num in range(half_way)]
#         list2 = [unsorted[num] for num in range(half_way, len(unsorted))]

#         to_sort1 = merge_sort(list1,sorted)
#         to_sort2 = merge_sort(list2,sorted)

#         if to_sort1[0] < to_sort2[0]:
#             sorted.insert(0,(to_sort1.pop(0)))
#         else:
#             sorted.insert(0,(to_sort2.pop(0)))
#     else:
#         if unsorted[0] > unsorted[1]:
#             sorted.insert(0, unsorted[0])
#             sorted.insert(1, unsorted[1])
#         else:
#             sorted.insert(0, unsorted[1])
#             sorted.insert(1, unsorted[0])
#     return sorted