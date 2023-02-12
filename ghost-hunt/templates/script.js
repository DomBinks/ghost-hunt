const output = document.querySelector('#terminal-output');
const commandLine = document.querySelector('#command-line');

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
commandLine.addEventListener('keydown', (event) => {
  if (event.key === 'Enter') {
    const command = commandLine.value;
    const line = document.createElement('div');
    line.innerHTML = 'ghost-hunter@terminal:~$ ' + command;
    output.appendChild(line);
    commandLine.value = '';
    
    while (output.children.length > 23) {
      output.removeChild(output.firstChild);
    }
    
    const lines = output.querySelectorAll('div');
    for (const line of lines) {
      if (line.innerHTML.length > 120) {
        line.innerHTML = line.innerHTML.substr(0, 120) + '...';
      }
    }
  }
});
