const output = document.querySelector('#MainTitle');

function typeASCIIArt() {
    const art = `
    /$$$$$$  /$$   /$$  /$$$$$$   /$$$$$$  /$$$$$$$$       /$$   /$$ /$$   /$$ /$$   /$$ /$$$$$$$$
   /$$__  $$| $$  | $$ /$$__  $$ /$$__  $$|__  $$__/      | $$  | $$| $$  | $$| $$$ | $$|__  $$__/
  | $$  |__/| $$  | $$| $$  | $$| $$  |__/   | $$         | $$  | $$| $$  | $$| $$$$| $$   | $$   
  | $$ /$$$$| $$$$$$$$| $$  | $$|  $$$$$$    | $$         | $$$$$$$$| $$  | $$| $$ $$ $$   | $$   
  | $$|_  $$| $$__  $$| $$  | $$ |____  $$   | $$         | $$__  $$| $$  | $$| $$  $$$$   | $$   
  | $$  | $$| $$  | $$| $$  | $$ /$$  | $$   | $$         | $$  | $$| $$  | $$| $$|  $$$   | $$   
  |  $$$$$$/| $$  | $$|  $$$$$$/|  $$$$$$/   | $$         | $$  | $$|  $$$$$$/| $$ |  $$   | $$   
   |______/ |__/  |__/ |______/  |______/    |__/         |__/  |__/ |______/ |__/  |__/   |__/   
    `;
    
    let i = 0;
    const type = setInterval(() => {
      output.innerHTML = art.substring(0, i);
      i++;
      if (i > art.length) {
        clearInterval(type);
      }
    }, 3);
  }

typeASCIIArt();