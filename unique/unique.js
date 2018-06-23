/*
 * 统计计数的JavaScript版本 
 */

const unique = (list = [], callback) => {
  const length = list.sort((a, b) => a - b).length;

  if (length === 0) return;

  let left = right = 0;

  for (; right < length; right++)
    if (list[right] !== list[left]) {
      const message = `${list[left]}: ${right - left}`;
      callback(message);
      left = right;
    }

  // 最后一步
  callback(`${list[left]}:${right - left}`);
}

const exampleList = [1, 9, 0, 2, 12, 2, 4, 8, 9, 7, 3, 3, 3, -1, -2];

unique(exampleList, console.log)
