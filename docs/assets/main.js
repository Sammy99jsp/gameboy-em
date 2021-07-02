function htmlForInstruction({opcode, syntax, description, flags, cycles}) {
    const [Z, N, H, C] = (flags || []).map(flagParse);
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

function parseSyntax(elements) {
    return elements.map(token => 
        `<div class="${token.type} token">${token.value}</div>`
    ).join(" ");
}

function flagParse(flag) {
    const acros = {R: "reset", S: "set", C: "conditional"};
    return acros[flag.toUpperCase()];
}

const OPCODES = [
    {
        opcode: "00",
        syntax: [{type: "mnemonic", value: "NOP"}],
        description: "No instruction. Does nothing for four cycles.",
        cycles: 4
    },
    {
        opcode: "CB 37",
        syntax: [{type: "mnemonic", value: "SWAP"}, {type: "register", value: "A"}],
        description: "Swap upper and lower nibbles of A",
        cycles: 8,
        flags: ["C", "R", "R", "R"]
    }
];

OPCODES.forEach(opcode => {
    $('#opcodes').append(htmlForInstruction(opcode));
})