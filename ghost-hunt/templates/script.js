const output = document.querySelector('#terminal-output');
const commandLine = document.querySelector('#command-line');

commandLine.addEventListener('keydown', (event) => {
  if (event.key === 'Enter') {
    const command = commandLine.value;
    const line = document.createElement('div');
    line.innerHTML = 'ghost-hunter@terminal:~$ ' + command;
    output.appendChild(line);
    commandLine.value = '';
    
    while (output.children.length > 10) {
      output.removeChild(output.firstChild);
    }
    
    const lines = output.querySelectorAll('div');
    for (const line of lines) {
      if (line.innerHTML.length > 80) {
        line.innerHTML = line.innerHTML.substr(0, 80) + '...';
      }
    }
  }
});
