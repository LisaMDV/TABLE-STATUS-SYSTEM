const char MAIN_page[] PROGMEM = R"=====(

<!DOCTYPE html>
<html>
      <head>
            <meta name="viewport" content="width=device-width, initial-scale=1">
            <link href="https://use.fontawesome.com/releases/v5.7.2/css/all.css" rel="stylesheet">
            

            <style>
              html {
              font-family: Arial;
              display: inline-block;
              margin: 0px auto;
              text-align: center;
              }
              h1 { font-size: 2.0rem; }
              p { font-size: 1.5rem; }
            </style>
            


            <style>
              .button {
                display: inline-block;
                padding: 15px 25px;
                font-size: 24px;
                cursor: pointer;
                text-align: center;
                text-decoration: none;
                outline: none;
                color: #fff;
                background-color: #4CAF50;
                border: none;
                border-radius: 15px;
                box-shadow: 0 8px #999;
              }

              .button:hover {background-color: #3e8e41}

              .button:active {
                background-color: #3e8e41;
                box-shadow: 0 5px #666;
                transform: translateY(4px);
              }
                .button.selected {
                  background-color: #F44336;
                }
              
            </style>


            <button class="button">Table 1</button>
            <button class="button">Table 2</button>
            <button class="button">Table 3</button>          
            <button class="button">Table 4</button>
            <br>
            <br>
            <button class="button">Table 5</button>          
            <button class="button">Table 6</button>
            <button class="button">Table 7</button>
            <button class="button">Table 8</button>


      </head>

      
      <body>
          <h1>NodeMCU V3 ESP8266/ESP12E RFID RC522</h1>
          <p style="color:#2e86c1;">THE UID OF THE SCANNED CARD IS : <span style="color:#17a589;" id="UIDResult"> </span></p>
         
          
          <script>
                setInterval(function() {
                  // Call a function repetatively with 0.1 (100ms) Second interval
                  getData();
                }, 100); 
            
                function getData() {
                  var xhttp = new XMLHttpRequest();
                
                  xhttp.onreadystatechange = function() {
                    if (this.readyState == 4 && this.status == 200) {
                      document.getElementById("UIDResult").innerHTML = this.responseText;
                            
                            // Reset the value of UIDResult after 3 seconds
                            setTimeout(function() {
                              document.getElementById("UIDResult").innerHTML = "";
                            }, 2000);

                      
                            // Get the button elements
                            var button1 = document.querySelector("button.button:nth-child(1)");
                            var button2 = document.querySelector("button.button:nth-child(2)");
                            var button3 = document.querySelector("button.button:nth-child(3)");
                            var button4 = document.querySelector("button.button:nth-child(4)");
                            var button5 = document.querySelector("button.button:nth-child(5)");
                            var button6 = document.querySelector("button.button:nth-child(6)");
                            var button7 = document.querySelector("button.button:nth-child(7)");
                            var button8 = document.querySelector("button.button:nth-child(8)");


                            button1.addEventListener("click", function() {
                              this.classList.toggle("selected");
                            });
                            button2.addEventListener("click", function() {
                              this.classList.toggle("selected");
                            });
                            button3.addEventListener("click", function() {
                              this.classList.toggle("selected");
                            });
                            button4.addEventListener("click", function() {
                              this.classList.toggle("selected");
                            });
                            button5.addEventListener("click", function() {
                              this.classList.toggle("selected");
                            });
                            button6.addEventListener("click", function() {
                              this.classList.toggle("selected");
                            });
                            button7.addEventListener("click", function() {
                              this.classList.toggle("selected");
                            });
                            button8.addEventListener("click", function() {
                              this.classList.toggle("selected");
                            });
                            
                            // Use a switch statement to toggle the color of the buttons based on the value of UIDResult
                            switch (this.responseText) {
                              case "901C2D20":
                                button1.classList.toggle("selected");
                                break;
                              case "A330EA1B":
                                button2.classList.toggle("selected");
                                break;
                              case "B313AD1D":
                                button3.classList.toggle("selected");
                                break;
                              case "906ED220":
                                button4.classList.toggle("selected");
                                break;
                              case "FFFFFFF2":
                                button5.classList.toggle("selected");
                                break;
                              case "FFFFFFF3":
                                button6.classList.toggle("selected");
                                break;
                              case "FFFFFFF4":
                                button7.classList.toggle("selected");
                                break;
                              case "FFFFFFF5":
                                button8.classList.toggle("selected");
                                break;  

                            }
                    }
                  };
                  xhttp.open("GET", "UIDResult", true);
                  xhttp.send();
                }
          </script>
      </body>

      
</html>








)=====";
