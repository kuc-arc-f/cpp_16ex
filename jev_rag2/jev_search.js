import koffi from "koffi"

const lib = koffi.load('./libsample.so');

const main = async function(){
  try{
    console.log(process.argv);

    // 3番目以降の引数だけを取得して処理する
    const args = process.argv.slice(2);
    let query = "";
    args.forEach((val, index) => {
      //console.log(`${index}: ${val}`);
      query = val;
    });
    console.log("query=", query);
    //return ;
    const jev_search = lib.func('char* jev_search(const char* input)');
    const resp =jev_search(query)
    console.log("\n" + "result=========")
    if(resp){
      console.log(resp)
    }else{
      console.log("nothing, result")
    }
  }catch(e){console.log(e)}
}
main();