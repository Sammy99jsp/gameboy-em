$('.container').on("scroll", function(e){
    localStorage.setItem("scroll-pos", $('.container').scrollTop());
});
let isInPopup = false;

let finished = [];

if(!localStorage.getItem("finished")) {
    localStorage.setItem("finished", JSON.stringify(finished));
} else {
    try {
        finished = JSON.stringify(localStorage.getItem("finished"));
    } catch(e) {
        localStorage.setItem("finished", JSON.stringify(finished));
    }
}

$(document).on('click', '.card', function(e) {
    if(!e.ctrlKey) return;
    let code = $(this).data("code");
    $(this).fadeOut('fast', function() {
        $(this).remove();
        finished.push(code);
    })
    localStorage.setItem("finished", JSON.stringify(finished));

})

$(document).on('mouseenter', '.mnemonic.token', function() {
    let el = $(this);
    let mnemonic = el.html();
    let popup = $(makePopup({content: MNEMONICS[mnemonic]}));
    popup.appendTo(el);
    popup.css({top: el.position().top + el.height() + 5, left: el.position().left + el.width() / 2 - popup.width() / 2})
    isInPopup = true;
});

$(document).on('mouseleave', '.mnemonic.token', function() {
    isInPopup = false;
    $(this).find('.popup').remove();
});

const LISTER = new Intl.ListFormat('en', { style: 'long', type: 'conjunction' });


$(document).on('mouseenter', '.token.condition', function() {
    let el = $(this);
    let cs = el.html().split("").map(cond => `<span class="wiki token condition">${cond}</span>`);
    let popup = $(makePopup({content: `If the ${LISTER.format(cs)} ${cs.length > 1 ? "flags are": "flag is"} set.`}));
    popup.appendTo(el);
    popup.css({top: el.position().top + el.height() + 5, left: el.position().left + el.width() / 2 - popup.width() / 2})
    isInPopup = true;
});

$(document).on('mouseleave', '.token.condition', function() {
    isInPopup = false;
    $(this).find('.popup').remove();
});

$(document).on('mouseenter', '.flag', function() {
    let f = $(this);
    if(f.hasClass("reset")) {
        $(this).attr("title", "Flag Reset.");
    } else if(f.hasClass("set")) {
        $(this).attr("title", "Flag Set.");
    } else if(f.hasClass("conditional")) {
        $(this).attr("title", "Flag dependent on operation's output.");
    } else {
        $(this).attr("title", "Flag Unaffected.")
    }
})

$(document).on('click', 'a', function(e) {
    let win = window.open($(this).attr('href'), '_blank');
    if(win) {
        win.focus();
        e.preventDefault();
    }
})


function makePopup({content}) {
   return (`<div class="popup">${content}</div>`)
}

function htmlForInstruction({opcode, syntax, flags, cycles}) {
    const [Z, N, H, C] = ([...(flags || [])]).map(flagParse);
    return `<div class="card" data-code="${opcode}">
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
        return `<div class="${token.type} token">${(token.demarcator || "(")[0]}${token.value.map(processToken).join("")}${(token.demarcator || " )")[1]}</div>`
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

    reference — Any reference to memory denoted with (XX), or anything in brackets []

    operator — A maths operator like + - * /
*/

window.instructions.sort(function(a, b) {
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