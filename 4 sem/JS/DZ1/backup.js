function isPalindrome1(str) {
    return str == str.split('').reverse().join('');
}

function isPalindrome2(string) {
    string = string.toLowerCase().replace(/\W/g, '');  //NEW!
    const stringArray = [...string];
    const newArray = [];
    stringArray.forEach(index => {
      newArray.unshift(index);
    });
    const reversedString = newArray.join('');
    console.log(string);
    return string === reversedString;
  }
console.log(isPalindrome2('racecar'));
//what is ...string? in JavaScript
//https://developer.mozilla.org/en-US/docs/Web/JavaScript/Reference/Operators/Spread_syntax

// Удаляем из строки все символы, кроме букв и цифр, и переводим все символы в нижний регистр
str = str.replace(/[^A-Za-z0-9]/g, '').toLowerCase();