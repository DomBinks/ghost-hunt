const inputField = document.getElementById("input-field");
const cursor = document.getElementById("cursor");

inputField.addEventListener("input", updateCursorPosition);
inputField.addEventListener("click", updateCursorPosition);

function updateCursorPosition() {
  cursor.style.top = inputField.offsetTop + inputField.offsetHeight - 2 + "px";
  cursor.style.left = inputField.offsetLeft + inputField.selectionEnd * 8 + "px";
}

const form = document.querySelector("form");

form.addEventListener("submit", function(event) {
    event.preventDefault();
    const userInput = inputField.value;
    const terminalOutput = document.createElement("p");
    terminalOutput.innerHTML = userInput;
  
    fetch("/your-endpoint", {
      method: "POST",
      headers: {
        "Content-Type": "application/json"
      },
      body: JSON.stringify({
        userInput: userInput
      })
    })
      .then(response => response.json())
      .then(data => {
        console.log(data);
      });
  
    document.querySelector(".terminal-body").appendChild(terminalOutput);
    inputField.value = "";
  });

const typingText = "This is the description section where you can describe the ghost.";
const typeSpeed = 50;
let i = 0;

function type() {
  if (i < typingText.length) {
    document.querySelector(".description-section p").innerHTML += typingText.charAt(i);
    i++;
    setTimeout(type, typeSpeed);
  }
}

window.addEventListener("load", type);
