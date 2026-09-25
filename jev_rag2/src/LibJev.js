import { choice, score, TypeSafeClient } from "@typesafe-ai/sdk";

const client = new TypeSafeClient();

export const getJevResult = async function(target , in_arr){
 try{
    const dim1 = in_arr;
    const response = await client.systemOne({
      state: { document: "似ている文章を探して欲しい。" },
      questions: {
        category: score(target, dim1),
      },
    });
    //console.log(response.answers.category.legend);
    //console.log(response.answers.category.probabilities);
    const r1 = response.answers.category.probabilities;
    const arr1 = Object.entries(r1).map(([key, value]) => ({ key, value }));
    //console.log(arr1)  
    let max_key = ""
    let max_value = 0
    arr1.forEach((element) => {
      //console.log(element)
      console.log(element.key)
      console.log(element.value)
      if(max_value === 0){
        max_key = element.key
        max_value = element.value;
      }
      if(element.value && (max_value < element.value)){
        max_key = element.key
        max_value = element.value;
      }
    });    
    console.log("max_key=", max_key)
    console.log("max_value=", max_value)
    const res1 = dim1[Number(max_key)];
    console.log("result=" , res1);
    return res1;
 }catch(e){console.log(e)}
}