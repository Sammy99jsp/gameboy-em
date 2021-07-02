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

const OPCODES = [
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
        opcode: "2A",
        syntax: [{type: "mnemonic", value: "LD"}, {type: "register", value: "A"}, {type: "reference", value: [{type: "register", value: "HL"}, {type: "operator", value: "++"}]}],
        description: "Load the value of memory at address HL, then increment HL.",
        cycles: 8,
        flags: "----"
    },
    {
        opcode: "F0",
        syntax: [{type: "mnemonic", value: "LD"}, {type: "register", value: "A"}, {type: "reference", value: [{type: "constant", value: "FF00"}, {type: "operator", value: "+"}, {type: "register", value: "A"}]}],
        description: "Load the value of ($FF00 + A) into A.",
        cycles: 12,
        flags: "----"
    },
    {
        opcode: "CB 37",
        syntax: [{type: "mnemonic", value: "SWAP"}, {type: "register", value: "A"}],
        description: "Swap upper and lower nibbles of A.",
        cycles: 8,
        flags: "CRRR"
    }
];

OPCODES.forEach(opcode => {
    $('#opcodes').append(htmlForInstruction(opcode));
})