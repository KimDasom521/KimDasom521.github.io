window.onload = function (){
    var desc =["안녕하세요? 김다솜입니다.",
    "반갑습니다.",
    "좋은 하루 되세요."];
    var index = 0;

    var interval = setInterval(function() {
            $('#book1_desc').fadeOut(500,function(){
                index++;
                if(index === desc.length)
                    index = 0;
                $(this).text(desc[index]).fadeIn(500);
            });
    }, 4000);

    var leftarrow = document.getElementById('left-arrow');
    var rightarrow = document.getElementById('right-arrow');

    leftarrow.onclick = function () {
        $('#book1_desc').fadeOut(500,function(){
            index--;
            if (index === -1)
                index = 2;
            $(this).text(desc[index]).fadeIn(500);
            clearInterval(interval);
        })
    }
            
    rightarrow.onclick = function () {
        $('#book1_desc').fadeOut(500,function(){
            index++;
            if (index === desc.length)
                index = 0;
            $(this).text(desc[index]).fadeIn(500);
            clearInterval(interval);
            
        })
    }
    
}