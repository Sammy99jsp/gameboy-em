


$('.container').on("scroll", function(e){
    localStorage.setItem("scroll-pos", $('.container').scrollTop());
});
function htmlForInstruction({opcode, syntax, description, flags, cycles}) {
    const [Z, N, H, C] = ([...(flags || [])]).map(flagParse);
    return `<div class="card">
    <div class="instruction">
        <div class="code">
            <div class="center-block">
                <div class="${opcode.length > 2 ? "smaller": ""} opcode">${opcode || "??"}</div>
                <div class="small-text">opcode</div>
            </div>
        </div>
        <div class="details">
            <div class="title">
                ${parseSyntax(syntax)}
            </div>
            <p>${description}</p>
        </div>
    </div>
    <div class="meta">
        <div class="cycles">
            <i class="ri-cpu-line icon"></i>
            <span class="text">Cycles: <span class="cycle-number">${cycles || "?"}</span></span>
        </div>
        <div class="flags">
            <i class="ri-flag-fill icon"></i>
            <div class="${Z || ""} flag">Z</div>
            <div class="${N || ""} flag">N</div>
            <div class="${H || ""} flag">H</div>
            <div class="${C || ""} flag">C</div>
        </div>
    </div>
  </div>`
}

function processToken(token) {
    if(token.type === "reference") {
        return `<div class="${token.type} token">${(token.demarcator || ["("])[0]}${token.value.map(processToken).join("")}${(token.demarcator || [, ")"])[1]}</div>`
    }
    return `<div class="${token.type} token">${token.value}</div>`;
}

function parseSyntax(elements, commas=true) {
    let processed =  elements.map(processToken);
    if(commas && ((elements[2] || {type: "null"}).type == "reference")) {
        return processed[0] + " " + processed.slice(1).join(",");
    }
    return processed[0] + " " + ( commas ? processed.slice(1).join(", "): processed.slice(1).join(""));
}

function flagParse(flag) {
    const acros = {R: "reset", S: "set", C: "conditional", "-": "unaffected"};
    return acros[flag.toUpperCase()];
}

/*
    TOKEN TYPES

    mnemonic — For an Instuction Mnemonic 

    register — For registers as parameters

    variable — For any variables in instruction

    constant — For a constant

    reference — Any reference to memory denoted with (XX)

    operator — A maths operator like + - * /
*/

/*const OPCODES = [
    {
        opcode: "00",
        syntax: [{type: "mnemonic", value: "NOP"}],
        description: "No instruction. Does nothing for four cycles.",
        cycles: 4,
        flags: "----"
    },
    {
        opcode: "01",
        syntax: [{type: "mnemonic", value: "LD"}, {type: "register", value: "BC"}, {type: "variable", value: "nn"}],
        description: "Loads a 16-bit value into register pair BC.",
        cycles: 12,
        flags: "----"
    },
    {
        opcode: "02",
        syntax: [{type: "mnemonic", value: "LD"}, {type: "reference", value: [{type: "register", value: "BC"}]}, {type: "register", value: "A"}],
        description: "Loads the value of A into memory at address BC.",
        cycles: 8,
        flags: "----"
    },
    {
        opcode: "03",
        syntax: [{type: "mnemonic", value: "INC"}, {type: "register", value: "BC"}],
        description: "Increment the BC register pair.",
        cycles: 8,
        flags: "----"
    },
    {
        opcode: "04",
        syntax: [{type: "mnemonic", value: "INC"}, {type: "register", value: "B"}],
        description: "Increment the B register.",
        cycles: 4,
        flags: "CRC-"
    },
    {
        opcode: "05",
        syntax: [{type: "mnemonic", value: "DEC"}, {type: "register", value: "B"}],
        description: "Decrement the B register.",
        cycles: 4,
        flags: "CSC-"
    },
    {
        opcode: "06",
        syntax: [{type: "mnemonic", value: "LD"}, {type: "register", value: "B"}, {type: "variable", value: "n"}],
        description: "Loads an 8-bit value into register B.",
        cycles: 8,
        flags: "----"
    },
    {
        opcode: "07",
        syntax: [{type: "mnemonic", value: "RLC"}, {type: "register", value: "A"}],
        description: "Rotate A to the left. And put the old bit 7 into the Carry flag.",
        cycles: 4,
        flags: "CRRC"
    },
    {
        opcode: "08",
        syntax: [{type: "mnemonic", value: "LD"}, {type: "reference", value: [{type: "variable", value: "nn"}]}, {type: "register", value: "SP"}],
        description: "Set the Stack Pointer to address nn. ",
        cycles: 20,
        flags: "----"
    },
    {
        opcode: "09",
        syntax: [{type: "mnemonic", value: "ADD"}, {type: "register", value: "HL"}, {type: "register", value: "BC"}],
        description: "Add BC to HL.",
        cycles: 8,
        flags: "-RCC"
    },
    {
        opcode: "0A",
        syntax: [{type: "mnemonic", value: "LD"}, {type: "register", value: "A"}, {type: "reference", value: [{type: "register", value: "BC"}]}],
        description: "Put value at address BC into A.",
        cycles: 8,
        flags: "----"
    },
    {
        opcode: "0B",
        syntax: [{type: "mnemonic", value: "DEC"}, {type: "register", value: "BC"}],
        description: "Decrement the BC register pair.",
        cycles: 8,
        flags: "----"
    },
    {
        opcode: "0C",
        syntax: [{type: "mnemonic", value: "INC"}, {type: "register", value: "C"}],
        description: "Increment the C register.",
        cycles: 4,
        flags: "CRC-"
    },
    {
        opcode: "0D",
        syntax: [{type: "mnemonic", value: "DEC"}, {type: "register", value: "C"}],
        description: "Decrement the C register.",
        cycles: 4,
        flags: "CSC-"
    },
    {
        opcode: "0E",
        syntax: [{type: "mnemonic", value: "LD"}, {type: "register", value: "C"}, {type: "variable", value: "n"}],
        description: "Put value n into C.",
        cycles: 4,
        flags: "----"
    },
    {
        opcode: "0F",
        syntax: [{type: "mnemonic", value: "RRC"}, {type: "register", value: "A"}],
        description: "Rotate A right and put the old 0 into the Carry flag.",
        cycles: 4,
        flags: "CRRC"
    },
    {
        opcode: "10 00",
        syntax: [{type: "mnemonic", value: "STOP"}],
        description: "Halt the CPU & LCD display until a button is pressed.",
        cycles: 4,
        flags: "----"
    },
    {
        opcode: "11",
        syntax: [{type: "mnemonic", value: "LD"}, {type: "register", value: "DE"}, {type: "variable", value: "nn"}],
        description: "Load a 16-bit value into the DE register pair.",
        cycles: 12,
        flags: "----"
    },
    {
        opcode: "12",
        syntax: [{type: "mnemonic", value: "LD"}, {type: "reference", value: [{type: "register", value: "DE"}]}, {type: "register", value: "A"}],
        description: "Put the value of A into address (DE)",
        cycles: 8
    },
    {
        opcode: "13",
        syntax: [{type: "mnemonic", value: "INC"}, {type: "register", value: "DE"}],
        description: "Increments the value of register pair DE.",
        cycles: 8
    },
    {
        opcode: "14",
        syntax: [{type: "mnemonic", value: "INC"}, {type: "register", value: "D"}],
        description: "Increments the value of the D register.",
        cycles: 4,
        flags: "CRC-"
    },
    {
        opcode: "15",
        syntax: [{type: "mnemonic", value: "DEC"}, {type: "register", value: "D"}],
        description: "Decrements the value of the D register.",
        cycles: 4,
        flags: "CSC-"
    },
    {
        opcode: "16",
        syntax: [{type: "mnemonic", value: "LD"}, {type: "variable", value: "n"}],
        description: "Load an 8-bit value into the D register.",
        cycles: 8,
        flags: "----"
    },
    {
        opcode: "17",
        syntax: [{type: "mnemonic", value: "RL"}, {type: "register", value: "A"}],
        description: "Rotate register A left through the Carry flag.",
        cycles: 4,
        flags: "CRRC"
    },
    {
        opcode: "18",
        syntax: [{type: "mnemonic", value: "JR"}, {type: "register", value: "r"}],
        description: "Add r to the current instruction address and jump to it.",
        cycles: 8,
        flags: "----"
    },
    {
        opcode: "19",
        syntax: [{type: "mnemonic", value: "ADD"}, {type: "register", value: "HL"}, {type: "register", value: "DE"}],
        description: "Add DE to HL.",
        cycles: 8,
        flags: "-RCC"
    },
    {
        opcode: "1A",
        syntax: [{type: "mnemonic", value: "LD"}, {type: "register", value: "A"}, {type: "reference", value: [{type: "register", value: "DE"}]}],
        description: "Load the value at address DE into A.",
        cycles: 8,
        flags: "----"
    },
    {
        opcode: "1B",
        syntax: [{type: "mnemonic", value: "DEC"}, {type: "register", value: "DE"}],
        description: "Decrement the value in the DE register pair.",
        cycles: 8,
        flags: "----"
    },
    {
        opcode: "1C",
        syntax: [{type: "mnemonic", value: "INC"}, {type: "register", value: "E"}],
        description: "Increment the value of the E register.",
        cycles: 4,
        flags: "CRC-"
    },
    {
        opcode: "1D",
        syntax: [{type: "mnemonic", value: "DEC"}, {type: "register", value: "E"}],
        description: "Decrement the value of the E register.",
        cycles: 4,
        flags: "CSC-"
    }
];*/

window.instructions.sort(function(a, b) {
    console.log(a.opcode, b.opcode)
    const [A, B] = [a.opcode.split(" ").map(e => parseInt(e, 16)), b.opcode.split(" ").map(e => parseInt(e, 16))];
    return A[0] - B[0] === 0 ? A[1] - B[1] : A[0] - B[0];
}).forEach(opcode => {
    try {
        $('#opcodes').append(htmlForInstruction(opcode));
        
    } catch (error) {
        console.log(error);   
    }
})

if(localStorage.getItem("scroll-pos")) {
    $('.container').scrollTop(localStorage.getItem("scroll-pos"));
}