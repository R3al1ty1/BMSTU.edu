function isPalindrom1(str) {
    // Удаляем из строки все символы, кроме букв и цифр, и переводим все символы в нижний регистр
    str = str.replace(/[^A-Za-z0-9]/g, '').toLowerCase();
    // Сравниваем строку с перевернутой версией строки
    return str === str.split('').reverse().join('');
  }

  function isPalindrom2(str) {
    // Удаляем из строки все символы, кроме букв и цифр, и переводим все символы в нижний регистр
    str = str.replace(/[^A-Za-z0-9]/g, '').toLowerCase();
    // Используем два указателя, чтобы сравнивать символы с обоих концов строки
    let left = 0;
    let right = str.length - 1;
    while (left < right) {
      if (str[left] !== str[right]) {
        return false;
      }
      left++;
      right--;
    }
    return true;
  }

  var input = prompt("Введите строку:");

  console.log(isPalindrom1(input));
  console.log(isPalindrom2(input));
  console.log('---------------------------------')
  console.log(isPalindrom1('А роза упала на лапу Азора')); // true
  console.log(isPalindrom1('121')); // true
  console.log(isPalindrom1('Was it a car or a cat I saw?')); // true
  console.log(isPalindrom1('A man, a plan, a canal, Panama!')); // true
  console.log(isPalindrom1('Madam In Eden, I’m Adam')); // true
  console.log(isPalindrom1('Racecar')); // true
  console.log('---------------------------------')
  console.log(isPalindrom2('А роза упала на лапу Азора')); // true
  console.log(isPalindrom2('121')); // true
  console.log(isPalindrom2('Was it a car or a cat I saw?')); // true
  console.log(isPalindrom2('A man, a plan, a canal, Panama!')); // true
  console.log(isPalindrom2('Madam In Eden, I’m Adam')); // true
  console.log(isPalindrom2('Racecar')); // true

  console.log('---------------------------------')

  console.log(isPalindrom1('Hello, world!')); // false
  console.log(isPalindrom1('1234567890')); // false
  console.log(isPalindrom1('Web development is fun')); // false
  console.log(isPalindrom1('This is not a palindrome')); // false
  console.log(isPalindrom1('Palindrome, but not quite')); // false
  console.log('---------------------------------')
  console.log(isPalindrom2('Hello, world!')); // false
  console.log(isPalindrom2('1234567890')); // false
  console.log(isPalindrom2('Web development is fun')); // false
  console.log(isPalindrom2('This is not a palindrome')); // false
  console.log(isPalindrom2('Palindrome, but not quite')); // false
